#include "HashingAlgorithm.h"
#include <stdexcept> // For std::logic_error
#include <optional>

// Constructor
CuckooHashing::CuckooHashing(size_t table_size) 
    : table_size(table_size), hash_table1(table_size), hash_table2(table_size) {}

// Hash function 1
size_t CuckooHashing::_hash_function1(const std::string& key) const {
    std::hash<std::string> hash_fn;
    return hash_fn(key) % table_size;
}

// Hash function 2
size_t CuckooHashing::_hash_function2(const std::string& key) const {
    std::hash<std::string> hash_fn;
    return (hash_fn(key) / table_size) % table_size; // Modified for a different dispersion
}

// Insert method
void CuckooHashing::insert(const std::string& key, const std::string& value) {
    size_t pos1 = _hash_function1(key);
    if (!hash_table1[pos1] || hash_table1[pos1]->first == key) {
        hash_table1[pos1] = std::make_pair(key, value);
        return;
    }

    size_t pos2 = _hash_function2(key);
    if (!hash_table2[pos2] || hash_table2[pos2]->first == key) {
        hash_table2[pos2] = std::make_pair(key, value);
        return;
    }

    // Handle collision or rehash as needed
    // This might involve moving the existing item to its alternate location,
    // and possibly a chain of moves or rehashing.
}

// Remove method
void CuckooHashing::remove(const std::string& key) {
    size_t pos1 = _hash_function1(key);
    if (hash_table1[pos1] && hash_table1[pos1]->first == key) {
        hash_table1[pos1].reset();
        return;
    }
    size_t pos2 = _hash_function2(key);
    if (hash_table2[pos2] && hash_table2[pos2]->first == key) {
        hash_table2[pos2].reset();
        return;
    }
    // Key not found, no action is performed.
}

// Search method
std::string CuckooHashing::search(const std::string& key) {
    size_t pos1 = _hash_function1(key);
    if (hash_table1[pos1] && hash_table1[pos1]->first == key) {
        return hash_table1[pos1]->second;
    }
    size_t pos2 = _hash_function2(key);
    if (hash_table2[pos2] && hash_table2[pos2]->first == key) {
        return hash_table2[pos2]->second;
    }
    throw std::logic_error("Key not found");
}