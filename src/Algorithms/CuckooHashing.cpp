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

bool CuckooHashing::isTableFull() const {
    size_t occupied_slots = 0;
    for (const auto& slot : hash_table1) {
        if (slot) ++occupied_slots;
    }
    for (const auto& slot : hash_table2) {
        if (slot) ++occupied_slots;
    }
    // Consider rehashing if 70% of the table is filled
    return (static_cast<double>(occupied_slots) / (2 * table_size)) > 0.7;
}

void CuckooHashing::rehash() {
    table_size *= 2; // Double the table size
    std::vector<std::optional<std::pair<std::string, std::string>>> new_hash_table1(table_size);
    std::vector<std::optional<std::pair<std::string, std::string>>> new_hash_table2(table_size);

    // Re-insert elements into new tables
    for (const auto& slot : hash_table1) {
        if (slot) {
            // Simplified insert logic for rehashing; actual implementation may need to handle collisions again
            size_t new_pos = _hash_function1(slot->first) % table_size;
            new_hash_table1[new_pos] = slot;
        }
    }
    for (const auto& slot : hash_table2) {
        if (slot) {
            size_t new_pos = _hash_function2(slot->first) % table_size;
            new_hash_table2[new_pos] = slot;
        }
    }

    // Replace old tables with new ones
    hash_table1 = std::move(new_hash_table1);
    hash_table2 = std::move(new_hash_table2);
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
    std::pair<std::string, std::string> displaced = hash_table2[pos2].value(); // Save displaced pair
    hash_table2[pos2] = std::make_pair(key, value); // Insert the new key-value pair

    for (int attempt = 0; attempt < hash_table1.size(); ++attempt) { // Limit attempts to avoid infinite loop
        std::swap(displaced.first, displaced.second); // Swap key-value for the hash function calculation

        size_t newPos = _hash_function1(displaced.first);
        if (!hash_table1[newPos] || hash_table1[newPos]->first == displaced.first) {
            hash_table1[newPos] = displaced;
            return;
        }
        std::swap(displaced, hash_table1[newPos].value()); // Displace the existing pair

        newPos = _hash_function2(displaced.first);
        if (!hash_table2[newPos] || hash_table2[newPos]->first == displaced.first) {
            hash_table2[newPos] = displaced;
            return;
        }
        std::swap(displaced, hash_table2[newPos].value()); // Displace the existing pair again
    }

    // If we're here, it means we couldn't resolve the collision in the limited attempts
    // This is where you might want to rehash or resize the table
    if (isTableFull()) {
        rehash(); // Placeholder for rehashing logic
        insert(key, value); // Try inserting again after rehashing
    }
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

void CuckooHashing::printTableInfo(const std::string& filename) {
    size_t entriesTable1 = 0, entriesTable2 = 0;
    for (const auto& entry : hash_table1) {
        if (entry) ++entriesTable1;
    }
    for (const auto& entry : hash_table2) {
        if (entry) ++entriesTable2;
    }

    double loadFactor1 = static_cast<double>(entriesTable1) / table_size;
    double loadFactor2 = static_cast<double>(entriesTable2) / table_size;
    // Assuming 'rehashCount' tracks the number of rehashes; add this member if you haven't already.
    size_t totalEntries = entriesTable1 + entriesTable2;

    nlohmann::json j;
    j["table_size"] = table_size;
    j["load_factor_table1"] = loadFactor1;
    j["load_factor_table2"] = loadFactor2;
    j["entries_table1"] = entriesTable1;
    j["entries_table2"] = entriesTable2;
    j["total_entries"] = totalEntries;
    // Add rehash count if you track it: j["rehash_count"] = rehashCount;

    std::ofstream o(filename);
    o << j.dump(4); // Pretty print with 4 spaces indent
    o.close();
}