// HashTableTests.cpp

#include "HashTableTestFixtures.h"
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

// Adjusted to accept HashingAlgorithm pointer
void TestEnglishDictionary(HashingAlgorithm* hashTable, const std::string& out) {
    // Ensure the path to the file is correct relative to the executable or use an absolute path
    InsertFromFileAndPrintInfo(hashTable, "words.txt", "Results/EnglishDict_" + out, 20); // 20 Seconds limit
}
void TestRandomEnglish1Dictionary(HashingAlgorithm* hashTable, const std::string& out) {
    // Ensure the path to the file is correct relative to the executable or use an absolute path
    InsertFromFileAndPrintInfo(hashTable, "mixed_words1.txt", "Results/EnglishDict_R1" + out, 20); // 20 Seconds limit
}
void TestRandomEnglish2Dictionary(HashingAlgorithm* hashTable, const std::string& out) {
    // Ensure the path to the file is correct relative to the executable or use an absolute path
    InsertFromFileAndPrintInfo(hashTable, "mixed_words2.txt", "Results/EnglishDict_R2" + out, 20); // 20 Seconds limit
}
void TestRandomEnglish3Dictionary(HashingAlgorithm* hashTable, const std::string& out) {
    // Ensure the path to the file is correct relative to the executable or use an absolute path
    InsertFromFileAndPrintInfo(hashTable, "mixed_words3.txt", "Results/EnglishDict_R3" + out, 20); // 20 Seconds limit
}

// Test cases
TEST_F(ChainingTest, EnglishDictionary) {
    TestEnglishDictionary(hashTable, "Chaining.json");
    TestRandomEnglish1Dictionary(hashTable, "Chaining.json");
    TestRandomEnglish2Dictionary(hashTable, "Chaining.json");
    TestRandomEnglish3Dictionary(hashTable, "Chaining.json");
}

TEST_F(CuckooHashingTest, EnglishDictionary) {
    TestEnglishDictionary(hashTable, "Cuckoo.json");
    TestRandomEnglish1Dictionary(hashTable, "Cuckoo.json");
    TestRandomEnglish2Dictionary(hashTable, "Cuckoo.json");
    TestRandomEnglish3Dictionary(hashTable, "Cuckoo.json");
}

TEST_F(OpenAddressingTest, EnglishDictionary) {
    TestEnglishDictionary(hashTable, "OpenAddressing.json");
    TestRandomEnglish1Dictionary(hashTable, "OpenAddressing.json");
    TestRandomEnglish2Dictionary(hashTable, "OpenAddressing.json");
    TestRandomEnglish3Dictionary(hashTable, "OpenAddressing.json");
}