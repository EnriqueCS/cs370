#include <gtest/gtest.h>
#include "../C_Algorithms/HashingAlgorithm.h" // Make sure this path matches your Chaining implementation file location

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

// Test Insertion and Search
TEST_F(OpenAddressingTest, InsertAndSearch) {
    openAddressing->insert("key1", "value1");
    EXPECT_EQ(openAddressing->search("key1"), "value1");

    openAddressing->insert("key2", "value2");
    EXPECT_EQ(openAddressing->search("key2"), "value2");

    // Test searching for a non-existent key
    EXPECT_THROW(openAddressing->search("nonexistent"), std::logic_error);
}

// Test Removal
TEST_F(OpenAddressingTest, Remove) {
    openAddressing->insert("key1", "value1");
    openAddressing->insert("key2", "value2");

    openAddressing->remove("key1");
    // After removal, searching for "key1" should throw an exception
    EXPECT_THROW(openAddressing->search("key1"), std::logic_error);

    // Ensure "key2" is still retrievable
    EXPECT_EQ(openAddressing->search("key2"), "value2");
}

// Test Table Full Scenario
TEST_F(OpenAddressingTest, TableFull) {
    // Fill the table to its capacity
    for (size_t i = 0; i < 10; ++i) { // Assuming a table_size of 10
        openAddressing->insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    // Attempting another insertion should throw, indicating the table is full
    EXPECT_THROW(openAddressing->insert("overflow", "value"), std::runtime_error);
}