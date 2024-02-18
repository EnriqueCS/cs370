// HashTableTestFixtures.h

#ifndef HASH_TABLE_TEST_FIXTURES_H
#define HASH_TABLE_TEST_FIXTURES_H

#include <gtest/gtest.h>
#include "../Algorithms/HashingAlgorithm.h" // Adjust the path as needed
#include "nlohmann/json.hpp"
#include <chrono>
#include <fstream>
#include <iostream>

#define SIZE_VARIABLE 10000

// Function to insert data from a file and print hash table information
void InsertFromFileAndPrintInfo(HashingAlgorithm* hashTable, const std::string& fileName, const std::string& out, int durationInSeconds);

// Function to load JSON data from a file
nlohmann::json load_test_data(const std::string& jsonFilePath);

// Function to remove the "Data/" prefix from a string
std::string removeDataPrefix(const std::string& str);

// Function to test dictionaries based on JSON configuration
void TestDictionaries(HashingAlgorithm* hashTable, const std::string& jsonFilePath, const std::string& testCategory, const std::string& out);

// Test fixture for Chaining
class ChainingTest : public ::testing::Test {
protected:
    Chaining* hashTable;

    void SetUp() override {
        hashTable = new Chaining(SIZE_VARIABLE);
    }

    void TearDown() override {
        delete hashTable;
    }
};

// Test fixture for CuckooHashing
class CuckooHashingTest : public ::testing::Test {
protected:
    CuckooHashing* hashTable;

    void SetUp() override {
        hashTable = new CuckooHashing(SIZE_VARIABLE);
    }

    void TearDown() override {
        delete hashTable;
    }
};

// Test fixture for OpenAddressing
class OpenAddressingTest : public ::testing::Test {
protected:
    OpenAddressing* hashTable;

    void SetUp() override {
        hashTable = new OpenAddressing(SIZE_VARIABLE);
    }

    void TearDown() override {
        delete hashTable;
    }
};

#endif // HASH_TABLE_TEST_FIXTURES_H