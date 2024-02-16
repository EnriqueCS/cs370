// HashTableTests.cpp

#include "HashTableTestFixtures.h"
#include <chrono>
#include <fstream>
#include <iostream>

// Assume HashingAlgorithm is a class that has insert and printTableInfo methods
void InsertFromFileAndPrintInfo(HashingAlgorithm* hashTable, const std::string& fileName, int durationInSeconds) {
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
    hashTable->printTableInfo();
}

// Adjusted to accept HashingAlgorithm pointer
void TestEnglishDictionary(HashingAlgorithm* hashTable) {
    // Ensure the path to the file is correct relative to the executable or use an absolute path
    InsertFromFileAndPrintInfo(hashTable, "words.txt", 20); // 20 Seconds limit
}

// Test cases
TEST_F(ChainingTest, EnglishDictionary) {
    TestEnglishDictionary(hashTable);
}

TEST_F(CuckooHashingTest, EnglishDictionary) {
    TestEnglishDictionary(hashTable);
}

TEST_F(OpenAddressingTest, EnglishDictionary) {
    TestEnglishDictionary(hashTable);
}