#include <gtest/gtest.h>
#include "HashingAlgorithm.h" // Include your hashing algorithm header
#include <fstream> // Include for file reading
#define SIZE_VARIABLE 10

// Test fixture for Chaining
class ChainingTest : public ::testing::Test {
protected:
    Chaining* hashTable;

    void SetUp() override {
        hashTable = new Chaining(SIZE_VARIABLE); // Initialize with table size of 10
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
        hashTable = new CuckooHashing(SIZE_VARIABLE); // Initialize with table size of 10
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
        hashTable = new OpenAddressing(SIZE_VARIABLE); // Initialize with table size of 10
    }

    void TearDown() override {
        delete hashTable;
    }
};