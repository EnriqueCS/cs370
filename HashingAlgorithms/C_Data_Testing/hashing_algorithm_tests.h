#include <gtest/gtest.h>
#include "HashingAlgorithm.h" // Include your hashing algorithm header

// Test fixture for Chaining
class ChainingTest : public ::testing::Test {
protected:
    Chaining* hashTable;

    void SetUp() override {
        hashTable = new Chaining(10); // Initialize with table size of 10
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
        hashTable = new CuckooHashing(10); // Initialize with table size of 10
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
        hashTable = new OpenAddressing(10); // Initialize with table size of 10
    }

    void TearDown() override {
        delete hashTable;
    }
};