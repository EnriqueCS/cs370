#include "./HashingConfig.h"

#ifndef HASHING_ALGORITHM_H
#define HASHING_ALGORITHM_H

#define LIMIT 128
typedef std::string String;
typedef std::vector<String> StringList;

class HashingAlgorithm {
public:
    size_t table_size;
    HashingAlgorithm(size_t size) : table_size(size) {}
    virtual ~HashingAlgorithm() {}
    virtual void insert(const String& value) = 0;
    virtual void remove(const String& value) = 0;
    virtual bool search(const String& value) = 0;
    size_t hash_function(const std::string& value) const {
        std::hash<std::string> hasher;
        return hasher(value) % table_size;
    }
};

struct Node {
    std::string key;
    std::shared_ptr<Node> next;

    Node(const std::string& key, std::shared_ptr<Node> next = nullptr)
        : key(key), next(next) {}
};

class Chaining : public HashingAlgorithm {
private:
    std::vector<std::shared_ptr<Node>> hash_table;
public:
    Chaining(size_t size = 10) : HashingAlgorithm(size) {
        hash_table.resize(table_size);
    }
    void insert(const std::string& key) override;
    void remove(const std::string& key) override;
    bool search(const std::string& key) override;
};

class CuckooHashing : public HashingAlgorithm {
private:
    std::vector<std::string> T_1, T_2;
    size_t hash_function2(const std::string& value) const;
    void rehash();

public:
    CuckooHashing(size_t size = 5) : HashingAlgorithm(size), 
        T_1(size, ""), T_2(size, "") {}
    void insert(const std::string& value) override;
    void remove(const std::string& value) override;
    bool search(const std::string& value) override;
};

class OpenAddressing : public HashingAlgorithm {
private:
    std::vector<std::string> hash_table;
    size_t count;
public:
    OpenAddressing(size_t size = 10): HashingAlgorithm(size), 
        hash_table(size, ""){}
    void insert(const String& value) override;
    void remove(const String& value) override;
    bool search(const String& value) override;
    void rehash();
};

class HashingFactory {
private:
    std::unique_ptr<HashingAlgorithm> algorithm;
public:
    HashingFactory(const HashingConfig& config) {
        switch (config.type) {
            case CHAINING:
                algorithm = std::make_unique<Chaining>(config.table_size);
                break;
            case CUCKOO_HASHING:
                algorithm = std::make_unique<CuckooHashing>(config.table_size);
                break;
            case OPEN_ADDRESSING:
                algorithm = std::make_unique<OpenAddressing>(config.table_size);
                break;
            default:
                throw std::invalid_argument("Invalid hashing algorithm type");
        }
    }

    void insert(const std::string& value) {
        algorithm->insert(value);
    }

    void remove(const std::string& value) {
        algorithm->remove(value);
    }

    bool search(const std::string& value) {
        return algorithm->search(value);
    }
};

#endif // HASHING_ALGORITHM_H