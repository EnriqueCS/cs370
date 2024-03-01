#ifndef HASH_TABLE_TESTS_H
#define HASH_TABLE_TESTS_H

#include <gtest/gtest.h>
#include "../Algorithms/HashingAlgorithm.h"


// Test Fixture for OpenAddressing
class OpenAddressingTest : public ::testing::Test {
protected:
    OpenAddressing* openAddressing;

    void SetUp() override {
        openAddressing = new OpenAddressing(10); // Initialize with a small table for testing
    }

    void TearDown() override {
        delete openAddressing;
    }
};

// Test Fixture for CuckooHashing
class CuckooHashingTest : public ::testing::Test {
protected:
    CuckooHashing* cuckooHashing;

    void SetUp() override {
        // Initialize CuckooHashing with a small table size for testing
        cuckooHashing = new CuckooHashing(10);
    }

    void TearDown() override {
        delete cuckooHashing;
    }
};

// Test Fixture for Chaining Hash Table
class ChainingTest : public ::testing::Test {
protected:
    Chaining* hashTable;

    void SetUp() override {
        // Initialize with a small table size to test collision handling easily
        hashTable = new Chaining(5);
    }

    void TearDown() override {
        delete hashTable;
    }
};

#endif // HASH_TABLE_TESTS_H
