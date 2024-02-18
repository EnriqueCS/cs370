// HashTableTests.cpp

#include "HashTableTestFixtures.h"

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
