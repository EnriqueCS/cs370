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

void Chaining::printTableInfo(const std::string& filename) {
    size_t totalEntries = 0;
    size_t emptyBuckets = 0;
    size_t maxLength = 0;
    size_t minLength = std::numeric_limits<size_t>::max();
    double totalChainLength = 0;

    for (const auto& bucket : hash_table) {
        size_t bucketSize = bucket.size();
        totalEntries += bucketSize;
        if (bucketSize == 0) ++emptyBuckets;
        else {
            if (bucketSize > maxLength) maxLength = bucketSize;
            if (bucketSize < minLength) minLength = bucketSize;
        }
        totalChainLength += bucketSize;
    }

    size_t nonEmptyBuckets = table_size - emptyBuckets;
    double averageChainLength = nonEmptyBuckets ? totalChainLength / nonEmptyBuckets : 0;
    double loadFactor = static_cast<double>(totalEntries) / table_size;

    nlohmann::json j;
    j["load_factor"] = loadFactor;
    j["average_chain_length"] = averageChainLength;
    j["max_chain_length"] = maxLength;
    j["min_chain_length"] = minLength == std::numeric_limits<size_t>::max() ? 0 : minLength;
    j["total_entries"] = totalEntries;
    j["empty_buckets"] = emptyBuckets;

    std::ofstream o(filename);
    o << j.dump(4); // Pretty print with 4 spaces indent
    o.close();
}