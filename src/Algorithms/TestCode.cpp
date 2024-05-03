#include "./HashingAlgorithm.h"

// Test insertion of a value
void testInsert(HashingFactory& factory, const std::string& value) {
    try {
        factory.insert(value);
    } catch (const std::exception& e) {
        std::cerr << "Insert Failed: ERROR" << e.what() << std::endl;
    }
}

// Test searching for a value
bool testSearch(HashingFactory& factory, const std::string& value) {
    try {
        return factory.search(value);
    } catch (const std::exception& e) {
        std::cerr << "Search Failed: ERROR" << e.what() << std::endl;
        return false;
    }
}

// Test removal of a value
void testRemove(HashingFactory& factory, const std::string& value) {
    try {
        factory.remove(value);
    } catch (const std::exception& e) {
        std::cerr << "Removal Failed: ERROR" << e.what() << std::endl;
    }
}

// Function to test all aspects of the hashing algorithm
void testHashingAlgorithm(const HashingAlgorithmConfig& config) {
    std::cout << "\nTesting " << config.getName() << "..." << std::endl;
    HashingConfig hashConfig = config.getHashConfig(10);
    HashingFactory factory(hashConfig);

    testInsert(factory, "TestValue");
    if(!testSearch(factory, "TestValue")){
        std::cout << "Test #1: Insert - Fail." << std::endl;
    }

    testRemove(factory, "TestValue");
    if(testSearch(factory, "TestValue")){
        std::cout << "Test #2: Remove - Fail." << std::endl;
    }

    testInsert(factory, "TestValue1");
    testInsert(factory, "TestValue2");
    testInsert(factory, "TestValue3");
    testInsert(factory, "TestValue4");
    testInsert(factory, "TestValue5");
    testInsert(factory, "TestValue6");
    testInsert(factory, "TestValue7");
    testInsert(factory, "TestValue8");
    testInsert(factory, "TestValue9");
    testInsert(factory, "TestValue10");
    if(!(
        testSearch(factory, "TestValue1") &&
        testSearch(factory, "TestValue2") &&
        testSearch(factory, "TestValue3") &&
        testSearch(factory, "TestValue4") &&
        testSearch(factory, "TestValue5") &&
        testSearch(factory, "TestValue6") &&
        testSearch(factory, "TestValue7") &&
        testSearch(factory, "TestValue8") &&
        testSearch(factory, "TestValue9") &&
        testSearch(factory, "TestValue10"))
    ){
        std::cout << "Test #3: Fill Table - Fail." << std::endl;
    }

    testRemove(factory, "TestValue1");
    testRemove(factory, "TestValue2");
    testRemove(factory, "TestValue3");
    testRemove(factory, "TestValue4");
    testRemove(factory, "TestValue5");
    testRemove(factory, "TestValue6");
    testRemove(factory, "TestValue7");
    testRemove(factory, "TestValue8");
    testRemove(factory, "TestValue9");
    testRemove(factory, "TestValue10");
    if(!(
        !testSearch(factory, "TestValue1") &&
        !testSearch(factory, "TestValue2") &&
        !testSearch(factory, "TestValue3") &&
        !testSearch(factory, "TestValue4") &&
        !testSearch(factory, "TestValue5") &&
        !testSearch(factory, "TestValue6") &&
        !testSearch(factory, "TestValue7") &&
        !testSearch(factory, "TestValue8") &&
        !testSearch(factory, "TestValue9") &&
        !testSearch(factory, "TestValue10"))
    ){
        std::cout << "Test #3: Fill Table - Fail." << std::endl;
    }
}

int main() {
    HashingAlgorithmConfig chainingConfig(HashingAlgorithmType::CHAINING);
    HashingAlgorithmConfig cuckooConfig(HashingAlgorithmType::CUCKOO_HASHING);
    HashingAlgorithmConfig openAddressingConfig(HashingAlgorithmType::OPEN_ADDRESSING);

    testHashingAlgorithm(chainingConfig);
    testHashingAlgorithm(cuckooConfig);
    testHashingAlgorithm(openAddressingConfig);

    return 0;
}
