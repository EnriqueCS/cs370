#include "HashingAlgorithm.h"
#include <stdexcept> // For std::runtime_error and std::logic_error
#include <optional>

// Constructor
OpenAddressing::OpenAddressing(size_t table_size)
    : table_size(table_size), hash_table(table_size), count(0) {}

// Hash function
size_t OpenAddressing::_hash_function(const std::string& key) const {
    std::hash<std::string> hash_fn;
    return hash_fn(key) % table_size;
}

// Insert method
void OpenAddressing::insert(const std::string& key, const std::string& value) {
    if (count == table_size) {
        throw std::runtime_error("Hash Table is full");
    }

    size_t index = _hash_function(key);
    for (size_t i = 0; i < table_size; ++i) {
        size_t probe_index = (index + i) % table_size;
        if (!hash_table[probe_index] || hash_table[probe_index]->first == key) {
            hash_table[probe_index] = std::make_pair(key, value);
            ++count;
            return;
        }
    }
}

// Remove method
void OpenAddressing::remove(const std::string& key) {
    size_t index = _hash_function(key);
    for (size_t i = 0; i < table_size; ++i) {
        size_t probe_index = (index + i) % table_size;
        if (hash_table[probe_index] && hash_table[probe_index]->first == key) {
            hash_table[probe_index].reset();
            --count;
            return;
        }
        if (!hash_table[probe_index]) {
            return; // Stop if an empty slot is found
        }
    }
}

// Search method
std::string OpenAddressing::search(const std::string& key) {
    size_t index = _hash_function(key);
    for (size_t i = 0; i < table_size; ++i) {
        size_t probe_index = (index + i) % table_size;
        if (hash_table[probe_index] && hash_table[probe_index]->first == key) {
            return hash_table[probe_index]->second;
        }
        if (!hash_table[probe_index]) {
            break; // Stop if an empty slot is found
        }
    }
    throw std::logic_error("Key not found");
}