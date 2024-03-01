#ifndef HASHING_ALGORITHM_H
#define HASHING_ALGORITHM_H

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <optional>
#include <list>

// Define type aliases to simplify the code further
typedef std::string String;
typedef std::pair<String, String> StringPair;
typedef std::list<StringPair> StringPairList;
typedef std::vector<StringPairList> HashTableList;
typedef std::vector<std::optional<StringPair>> HashTableOptional;

class HashingAlgorithm {
public:
    virtual ~HashingAlgorithm() {}
    virtual void insert(const String& key, const String& value) = 0;
    virtual void remove(const String& key) = 0;
    virtual String search(const String& key) = 0;
    virtual void printTableInfo(const String& filename) = 0;
};


// Enumeration to represent each algorithm
enum HashingAlgorithmType {
    CHAINING = 1,
    CUCKOO_HASHING = 2,
    OPEN_ADDRESSING = 3
};

class Chaining : public HashingAlgorithm {
private:
    HashTableList hash_table; // Simplified with typedef
    size_t table_size;
    size_t _hash_function(const String& key) const;

public:
    Chaining(size_t table_size = 10);
    void insert(const String& key, const String& value) override;
    void remove(const String& key) override;
    String search(const String& key) override;
    void printTableInfo(const String& filename) override;
};

class CuckooHashing : public HashingAlgorithm {
private:
    HashTableOptional hash_table1; // Simplified with typedef
    HashTableOptional hash_table2; // Simplified with typedef
    size_t _hash_function1(const String& key) const;
    size_t _hash_function2(const String& key) const;
    bool isTableFull() const;
    void rehash();
public:
    size_t table_size;
    CuckooHashing(size_t table_size = 10);
    void insert(const String& key, const String& value) override;
    void remove(const String& key) override;
    String search(const String& key) override;
    void printTableInfo(const String& filename) override;
};

class OpenAddressing : public HashingAlgorithm {
private:
    size_t _hash_function(const String& key) const;
    HashTableOptional hash_table; // Simplified with typedef
    size_t table_size;
    size_t count; // To keep track of the number of elements
public:
    OpenAddressing(size_t table_size = 10);
    void insert(const String& key, const String& value) override;
    void remove(const String& key) override;
    String search(const String& key) override;
    void printTableInfo(const String& filename) override;
    void rehash();
};

class HashingFactory {
private:
    std::unique_ptr<HashingAlgorithm> algorithm;
public:
    // Constructor that takes the algorithm type and initializes the correct hashing algorithm
    HashingFactory(HashingAlgorithmType type, size_t table_size = 10) {
        switch (type) {
            case CHAINING:
                algorithm = std::make_unique<Chaining>(table_size);
                break;
            case CUCKOO_HASHING:
                algorithm = std::make_unique<CuckooHashing>(table_size);
                break;
            case OPEN_ADDRESSING:
                algorithm = std::make_unique<OpenAddressing>(table_size);
                break;
            default:
                throw std::invalid_argument("Invalid hashing algorithm type");
        }
    }

    // Delegating calls to the encapsulated algorithm object
    void insert(const String& key, const String& value) {
        algorithm->insert(key, value);
    }

    void remove(const String& key) {
        algorithm->remove(key);
    }

    String search(const String& key) {
        return algorithm->search(key);
    }

    void printTableInfo(const String& filename) {
        algorithm->printTableInfo(filename);
    }
};

#endif // HASHING_ALGORITHM_H