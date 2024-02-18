#include <gtest/gtest.h>
#include "../Algorithms/HashingAlgorithm.h" // Make sure this path matches your Chaining implementation file location

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

// Test Insertion and Search
TEST_F(CuckooHashingTest, InsertAndSearch) {
    cuckooHashing->insert("key1", "value1");
    EXPECT_EQ(cuckooHashing->search("key1"), "value1");

    cuckooHashing->insert("key2", "value2");
    EXPECT_EQ(cuckooHashing->search("key2"), "value2");

    // Test to ensure that non-existent keys throw an exception
    EXPECT_THROW(cuckooHashing->search("nonexistent"), std::logic_error);
}

// Test Removal
TEST_F(CuckooHashingTest, Remove) {
    cuckooHashing->insert("key1", "value1");
    cuckooHashing->insert("key2", "value2");

    cuckooHashing->remove("key1");
    // After removal, searching for "key1" should throw an exception
    EXPECT_THROW(cuckooHashing->search("key1"), std::logic_error);

    // Ensure "key2" is still present
    EXPECT_EQ(cuckooHashing->search("key2"), "value2");
}

// Test Table Full Scenario with Rehashing
TEST_F(CuckooHashingTest, HandleRehashOnFull) {
    // Assuming table size is small and a full table scenario can be simulated easily
    for (size_t i = 0; i < cuckooHashing->table_size; ++i) {
        cuckooHashing->insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    // Inserting an extra key-value pair which should trigger rehashing if the table is full
    cuckooHashing->insert("extraKey", "extraValue");

    // Check if the extra key can be found, indicating successful rehashing and insertion
    std::string value = cuckooHashing->search("extraKey");
    EXPECT_EQ(value, "extraValue");
}