// HashTableTestFixtures.h

#ifndef HASH_TABLE_TEST_FIXTURES_H
#define HASH_TABLE_TEST_FIXTURES_H

#include <gtest/gtest.h>
#include "../C_Algorithms/HashingAlgorithm.h" // Adjust the path as needed

#define SIZE_VARIABLE 1000

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