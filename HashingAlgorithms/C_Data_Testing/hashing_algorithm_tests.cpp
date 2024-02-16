// Test inserting values and printing table info for Chaining
TEST_F(ChainingTest, InsertAndPrintInfo) {
    // Example inserts
    hashTable->insert("key1", "value1");
    hashTable->insert("key2", "value2");
    // Call printTableInfo at the end
    hashTable->printTableInfo();
    // Placeholder for actual test method to verify output
}

// Test inserting values and printing table info for CuckooHashing
TEST_F(CuckooHashingTest, InsertAndPrintInfo) {
    // Example inserts
    hashTable->insert("key1", "value1");
    hashTable->insert("key2", "value2");
    // Call printTableInfo at the end
    hashTable->printTableInfo();
    // Placeholder for actual test method to verify output
}

// Test inserting values and printing table info for OpenAddressing
TEST_F(OpenAddressingTest, InsertAndPrintInfo) {
    // Example inserts
    hashTable->insert("key1", "value1");
    hashTable->insert("key2", "value2");
    // Call printTableInfo at the end
    hashTable->printTableInfo();
    // Placeholder for actual test method to verify output
}