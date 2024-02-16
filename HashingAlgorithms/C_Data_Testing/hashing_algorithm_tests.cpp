// Helper function for reading from file and inserting into any hash table
void InsertFromFileAndPrintInfo(HashingAlgorithm* hashTable, const std::string& fileName) {
    std::ifstream file(fileName);
    std::string word;
    int keySuffix = 1; // To create unique keys for each word

    while (std::getline(file, word)) {
        std::string key = "key" + std::to_string(keySuffix++);
        hashTable->insert(key, word);
    }

    // Call printTableInfo at the end
    hashTable->printTableInfo();
}

void TestEnglishDictionary(HashTable& hashTable) {
    InsertFromFileAndPrintInfo(hashTable, "words.txt");
    // Placeholder for actual test method to verify output
}

TEST_F(ChainingTest, EnglishDictionary) {
    TestEnglishDictionary(hashTable);
}

TEST_F(CuckooHashingTest, EnglishDictionary) {
    TestEnglishDictionary(hashTable);
}

TEST_F(OpenAddressingTest, EnglishDictionary) {
    TestEnglishDictionary(hashTable);
}