#include <gtest/gtest.h>
#include "../Algorithms/HashingAlgorithm.h" // Make sure this path matches your Chaining implementation file location

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

// Test basic insertion and search
TEST_F(ChainingTest, HandlesInsertionAndSearch) {
    hashTable->insert("key1", "value1");
    ASSERT_EQ(hashTable->search("key1"), "value1");
    hashTable->insert("key2", "value2");
    ASSERT_EQ(hashTable->search("key2"), "value2");
}

// Test updating existing key
TEST_F(ChainingTest, HandlesUpdatingValue) {
    hashTable->insert("key1", "value1");
    hashTable->insert("key1", "updatedValue");
    ASSERT_EQ(hashTable->search("key1"), "updatedValue");
}

// Test collision handling
TEST_F(ChainingTest, HandlesCollisions) {
    // Assuming these keys result in the same hash index to simulate a collision
    hashTable->insert("key1", "value1");
    hashTable->insert("keyCollide", "valueCollide");
    ASSERT_EQ(hashTable->search("key1"), "value1");
    ASSERT_EQ(hashTable->search("keyCollide"), "valueCollide");
}

// Test deletion
TEST_F(ChainingTest, HandlesDeletion) {
    hashTable->insert("key1", "value1");
    hashTable->remove("key1");
    ASSERT_THROW(hashTable->search("key1"), std::logic_error); // Assuming search throws if key not found
}

// Test handling of non-existent key
TEST_F(ChainingTest, HandlesNonExistentKey) {
    ASSERT_THROW(hashTable->search("nonExistentKey"), std::logic_error); // Assuming search throws if key not found
}

// Stress Test
TEST_F(ChainingTest, StressTest) {
    // Insert a large number of elements
    for (int i = 0; i < 1000; ++i) {
        hashTable->insert("key" + std::to_string(i), "value" + std::to_string(i));
    }
    // Verify they are all searchable
    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(hashTable->search("key" + std::to_string(i)), "value" + std::to_string(i));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}