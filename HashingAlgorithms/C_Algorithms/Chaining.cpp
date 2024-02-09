#include <vector>
#include <list>
#include <string>
#include <utility> // For std::pair

class Chaining : public HashingAlgorithm {
private:
    std::vector<std::list<std::pair<std::string, std::string>>> hash_table;
    size_t table_size;

    size_t _hash_function(const std::string& key) const {
        // Simple hash function for demonstration, using std::hash
        std::hash<std::string> hash_fn;
        return hash_fn(key) % table_size;
    }

public:
    Chaining(size_t table_size = 10) : table_size(table_size), hash_table(table_size) {}

    void insert(const std::string& key, const std::string& value) override {
        size_t index = _hash_function(key);
        // Check for existing key and update
        for (auto& pair : hash_table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        // Otherwise, append new key-value pair
        hash_table[index].emplace_back(key, value);
    }

    void remove(const std::string& key) override {
        size_t index = _hash_function(key);
        for (auto it = hash_table[index].begin(); it != hash_table[index].end(); ++it) {
            if (it->first == key) {
                hash_table[index].erase(it);
                return;
            }
        }
    }

    std::string search(const std::string& key) override {
        size_t index = _hash_function(key);
        for (const auto& pair : hash_table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::logic_error("Key not found");
    }
};