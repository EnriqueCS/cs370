#include "HashingAlgorithm.h"
#include <stdexcept> // For std::logic_error

// Constructor
Chaining::Chaining(size_t table_size) : table_size(table_size), hash_table(table_size) {}

// Insert method
void Chaining::insert(const std::string& key, const std::string& value) {
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

// Remove method
void Chaining::remove(const std::string& key) {
    size_t index = _hash_function(key);
    for (auto it = hash_table[index].begin(); it != hash_table[index].end(); ++it) {
        if (it->first == key) {
            hash_table[index].erase(it);
            return;
        }
    }
}

// Search method
std::string Chaining::search(const std::string& key) {
    size_t index = _hash_function(key);
    for (const auto& pair : hash_table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    throw std::logic_error("Key not found");
}

// Hash function
size_t Chaining::_hash_function(const std::string& key) const {
    std::hash<std::string> hash_fn;
    return hash_fn(key) % table_size;
}