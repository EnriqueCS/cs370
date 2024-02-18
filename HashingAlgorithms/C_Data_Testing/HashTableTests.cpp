// HashTableTests.cpp

#include "HashTableTestFixtures.h"
#include "nlohmann/json.hpp"
#include <chrono>
#include <fstream>
#include <iostream>

// Assume HashingAlgorithm is a class that has insert and printTableInfo methods
void InsertFromFileAndPrintInfo(HashingAlgorithm* hashTable, const std::string& fileName,const std::string& out, int durationInSeconds) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    std::string word;
    int keySuffix = 1; // To create unique keys for each word

    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    while (std::getline(file, word)) {
        // Check elapsed time
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start);
        if (elapsed.count() >= durationInSeconds) {
            std::cout << "Time limit of " << durationInSeconds << " seconds reached. Stopping insertion." << std::endl;
            break; // Stop inserting if the time limit has been reached
        }

        std::string key = "key" + std::to_string(keySuffix++);
        hashTable->insert(key, word);
    }

    // Call printTableInfo at the end
    hashTable->printTableInfo(out);
}


// Function to load JSON data from a file
nlohmann::json load_test_data(const std::string& jsonFilePath) {
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open JSON file: " << jsonFilePath << std::endl;
        exit(1);
    }
    nlohmann::json jsonData;
    file >> jsonData;
    return jsonData;
}

std::string removeDataPrefix(const std::string& str) {
    std::string prefix = "Data/";
    if (str.substr(0, prefix.size()) == prefix) {
        return str.substr(prefix.size());
    }
    return str;
}

// Refactored function to test dictionaries
void TestDictionaries(HashingAlgorithm* hashTable, const std::string& jsonFilePath, const std::string& testCategory, const std::string& out) {
    std::cout << "Loading test data from: " << jsonFilePath << std::endl; // Debug print
    auto testData = load_test_data(jsonFilePath);

    if (testData.find(testCategory) == testData.end()) {
        std::cout << "Test category '" << testCategory << "' not found in JSON file." << std::endl; // Debug print
        return;
    }

    for (const auto& filePathJson : testData[testCategory]) {
        // Convert the JSON element to std::string
        std::string filePath = filePathJson.get<std::string>();

        // Extract the filename from the filePath
        size_t lastSlashPos = filePath.find_last_of("/\\") + 1;
        std::string fileName = filePath.substr(lastSlashPos);
        
        // Optionally, remove the file extension if needed
        size_t lastDotPos = fileName.find_last_of('.');
        std::string fileNameWithoutExt = (lastDotPos != std::string::npos) ? fileName.substr(0, lastDotPos) : fileName;
        
        std::string resultPath = "Results/" + 
                                removeDataPrefix(testCategory) + 
                                "/" + 
                                fileNameWithoutExt +  // Use the filename without the extension
                                "/" + 
                                out;  // Append the output file designation

        std::cout << "Testing file: " << filePath << " with result path: " << resultPath << std::endl; // Debug print
        InsertFromFileAndPrintInfo(hashTable, filePath, resultPath, 20); // 20 seconds limit
    }
}

// Example test case refactored
void RunAllTests(HashingAlgorithm* hashTable, const std::string& jsonFilePath, const std::string& outFileName) {
    TestDictionaries(hashTable, jsonFilePath, "Data/Census", outFileName);
    TestDictionaries(hashTable, jsonFilePath, "Data/English", outFileName);
}

TEST_F(ChainingTest, AllDictionaries) {
    RunAllTests(hashTable, "Data/files_structure.json", "Chaining.json");
}

TEST_F(CuckooHashingTest, AllDictionaries) {
    RunAllTests(hashTable, "Data/files_structure.json", "Cuckoo.json");
}

TEST_F(OpenAddressingTest, AllDictionaries) {
    RunAllTests(hashTable, "Data/files_structure.json", "OpenAddressing.json");
}
