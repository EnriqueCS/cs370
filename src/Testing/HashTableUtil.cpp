// HashTableTests.cpp

#include "HashTableTestFixtures.h"
#include <nlohmann/json.hpp>
#include <papi.h>

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

void savePapiCountersToJson(long long totalInstructions, long long cacheMisses, const std::string& outFilename) {
    nlohmann::json j;
    j["Total Instructions"] = totalInstructions;
    j["Level 1 Data Cache Misses"] = cacheMisses;

    std::ofstream outFile(outFilename);
    if (!outFile) {
        std::cerr << "Failed to open output file for writing JSON: " << outFilename << std::endl;
        return;
    }

    outFile << j.dump(4); // Dump the JSON with an indentation of 4 spaces
    outFile.close();

    std::cout << "PAPI counters saved to " << outFilename << std::endl;
}

// Function to check PAPI calls and print specific error messages
bool checkPapiCall(int resultCode, const std::string& errorMessage) {
    if (resultCode != PAPI_OK) {
        std::cerr << errorMessage << ": " << PAPI_strerror(resultCode) << std::endl;
        return false; // Return false to indicate failure
    }
    return true; // Return true to indicate success
}

void InsertFromFileAndPapiInfo(HashingAlgorithm* hashTable, const std::string& fileName, const std::string& out, int durationInSeconds) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    // Initialize PAPI
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        std::cerr << "PAPI library initialization error!" << std::endl;
        return;
    }

    // Create an event set and add Total Instructions and Level 1 Cache Misses
    int EventSet = PAPI_NULL;
    long_long values[2] = {0}; // To store the counter values

        // Create an event set
    if (!checkPapiCall(PAPI_create_eventset(&EventSet), "PAPI create event set error")) return;

    // Add Total Instructions event
    if (!checkPapiCall(PAPI_add_event(EventSet, PAPI_TOT_INS), "Error adding PAPI_TOT_INS")) return;

    // Add Level 1 Data Cache Misses event
    if (!checkPapiCall(PAPI_add_event(EventSet, PAPI_L1_DCM), "Error adding PAPI_L1_DCM")) return;

    // Start counting events
    if (!checkPapiCall(PAPI_start(EventSet), "PAPI start error")) return;

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

    // Stop PAPI and read the counters
    if (PAPI_stop(EventSet, values) != PAPI_OK) {
        std::cerr << "Error reading PAPI counters!" << std::endl;
    } else {
        std::cout << "Total instructions: " << values[0] << std::endl;
        std::cout << "Level 1 data cache misses: " << values[1] << std::endl;
    }

    PAPI_shutdown();
    savePapiCountersToJson(values[0], values[1], out);

    // Save the hash table information to a file, etc.
    // Assuming you implement this part
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

        std::string papiResultPath = "Results/" + 
                        removeDataPrefix(testCategory) + 
                        "/Papi_" + 
                        fileNameWithoutExt +  // Use the filename without the extension
                        "/" + 
                        out;  // Append the output file designation

        std::cout << "Testing file: " << filePath << " with result path: " << resultPath << std::endl; // Debug print
        InsertFromFileAndPrintInfo(hashTable, filePath, resultPath, 20); // 20 seconds limit
        // InsertFromFileAndPapiInfo(hashTable, filePath, papiResultPath, 20); // 20 seconds limit
    }
}
