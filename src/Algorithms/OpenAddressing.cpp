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

void OpenAddressing::rehash() {
    size_t new_table_size = table_size * 2; // Double the size
    std::vector<std::optional<std::pair<std::string, std::string>>> new_hash_table(new_table_size);

    // Rehash all existing elements
    for (auto& entry : hash_table) {
        if (entry) {
            size_t index = _hash_function(entry->first);
            for (size_t i = 0; i < new_table_size; ++i) {
                size_t probe_index = (index + i) % new_table_size;
                if (!new_hash_table[probe_index]) {
                    new_hash_table[probe_index] = *entry;
                    break;
                }
            }
        }
    }

    // Replace the old table with the new table
    hash_table = std::move(new_hash_table);
    table_size = new_table_size;
}

// Insert method
void OpenAddressing::insert(const std::string& key, const std::string& value) {
    if (count >= table_size) {
        rehash();
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

void OpenAddressing::printTableInfo(const std::string& filename) {
    double loadFactor = static_cast<double>(count) / table_size;
    std::vector<size_t> probeLengths(table_size, 0); // Vector to track probe lengths for each insert

    // Recalculate probe lengths for each filled slot to simulate insertion process
    for (size_t idx = 0; idx < table_size; ++idx) {
        if (hash_table[idx]) {
            size_t index = _hash_function(hash_table[idx]->first);
            size_t probeLength = 1;
            for (size_t i = 0; i < table_size; ++i) {
                size_t probe_index = (index + i) % table_size;
                if (probe_index == idx) {
                    probeLengths[idx] = probeLength;
                    break;
                }
                if (!hash_table[probe_index]) break; // Encounter an empty slot
                ++probeLength;
            }
        }
    }
    // Calculate average and maximum probe length
    double avgProbeLength = count > 0 ? std::accumulate(probeLengths.begin(), probeLengths.end(), 0.0) / count : 0;
    size_t maxProbeLength = *std::max_element(probeLengths.begin(), probeLengths.end());

    nlohmann::json j;
    j["table_size"] = table_size;
    j["load_factor"] = loadFactor;
    j["total_entries"] = count;
    j["average_probe_length"] = avgProbeLength;
    j["maximum_probe_length"] = maxProbeLength;

    std::ofstream o(filename);
    o << j.dump(4); // Pretty print with 4 spaces indent
    o.close();
}