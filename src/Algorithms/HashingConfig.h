#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <optional>
#include <list>
#include <limits>
#include <numeric>
#include <algorithm>
#include <memory>
#include <cstddef>

#ifndef HASHING_ALGORITHM_CONFIG_H
#define HASHING_ALGORITHM_CONFIG_H

// Enumeration to represent each algorithm
enum HashingAlgorithmType {
    CHAINING = 1,
    CUCKOO_HASHING = 2,
    OPEN_ADDRESSING = 3
};

// Define the HashingConfig structure
struct HashingConfig {
    HashingAlgorithmType type;
    size_t table_size;

    HashingConfig(HashingAlgorithmType type, size_t table_size) 
        : type(type), table_size(table_size) {}
};

struct HashingAlgorithmConfig {
    HashingAlgorithmType type;

    HashingAlgorithmConfig(HashingAlgorithmType type) : type(type) {}

    std::string getName() const {
        switch (type) {
            case HashingAlgorithmType::CHAINING:            return "Chaining";
            case HashingAlgorithmType::CUCKOO_HASHING:      return "Cuckoo";
            case HashingAlgorithmType::OPEN_ADDRESSING:     return "OpenAddressing";
            default:                                        return "Unknown";
        }
    }

    HashingConfig getHashConfig(size_t table_size) const {
        return HashingConfig(type, table_size);
    }
};

#endif // HASHING_ALGORITHM_CONFIG_H