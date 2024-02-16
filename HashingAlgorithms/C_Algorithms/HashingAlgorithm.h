// Ensure the include guard is already in place
#ifndef HASHING_ALGORITHM_H
#define HASHING_ALGORITHM_H

#include <stdexcept>
#include <string>
#include <vector>
#include <optional>
#include <list>

class HashingAlgorithm {
public:
    virtual ~HashingAlgorithm() {}
    virtual void insert(const std::string& key, const std::string& value) = 0;
    virtual void remove(const std::string& key) = 0;
    virtual std::string search(const std::string& key) = 0;
    virtual void printTableInfo() = 0;
};

class Chaining : public HashingAlgorithm {
private:
    std::vector<std::list<std::pair<std::string, std::string>>> hash_table; // Ensure declared here
    size_t table_size; // Ensure declared here
    size_t _hash_function(const std::string& key) const; // Ensure declared here

public:
    Chaining(size_t table_size = 10);
    void insert(const std::string& key, const std::string& value) override;
    void remove(const std::string& key) override;
    std::string search(const std::string& key) override;
    void printTableInfo() override;
};

class CuckooHashing : public HashingAlgorithm {
private:
    std::vector<std::optional<std::pair<std::string, std::string>>> hash_table1;
    std::vector<std::optional<std::pair<std::string, std::string>>> hash_table2;
    size_t _hash_function1(const std::string& key) const;
    size_t _hash_function2(const std::string& key) const;
    bool isTableFull() const;
    void rehash();
public:
    size_t table_size;
    CuckooHashing(size_t table_size = 10);
    void insert(const std::string& key, const std::string& value) override;
    void remove(const std::string& key) override;
    std::string search(const std::string& key) override;
    void printTableInfo() override;
};

class OpenAddressing : public HashingAlgorithm {
private:
    size_t _hash_function(const std::string& key) const;
    std::vector<std::optional<std::pair<std::string, std::string>>> hash_table;
    size_t table_size;
    size_t count; // To keep track of the number of elements
public:
    OpenAddressing(size_t table_size = 10);
    void insert(const std::string& key, const std::string& value) override;
    void remove(const std::string& key) override;
    std::string search(const std::string& key) override;
    void printTableInfo() override;
};

#endif // HASHING_ALGORITHM_H