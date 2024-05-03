#include "../HashingAlgorithm.h"
#include <vector>
#include <string>
#include <stdexcept>

void OpenAddressing::insert(const std::string& value) {
    size_t i = 0;
    size_t j = hash_function(value) % table_size;

    while (i < LIMIT) {
        if (hash_table[j] == "") {
            hash_table[j] = value;
            ++count;
            return;
        }
        j = (j + 1) % table_size;
        ++i;
    }
}

void OpenAddressing::remove(const std::string& value) {
    size_t i = 0;
    size_t j = hash_function(value);

    while (i < LIMIT) {
        if (hash_table[j] == "") return;
        if (hash_table[j] == value) {
            hash_table[j] = "";
            --count;
            return;
        }
        j = (j + 1) % table_size;  // Linear probing increment
        ++i;
    }
}

bool OpenAddressing::search(const std::string& value) {
    size_t i = 0;
    size_t j = hash_function(value);

    while (i < LIMIT) {
        if (hash_table[j] == "") {
            return false;
        } else if (hash_table[j] == value) {
            return true;
        }
        // Linear probing increment
        j = (j + 1) % table_size;
        ++i;
    }
    return false;
}

// Rehash function NOT IN USE
void OpenAddressing::rehash() {
    std::vector<std::string> old_table = hash_table;
    hash_table.clear();
    hash_table.resize(2 * table_size, "");
    table_size *= 2;
    count = 0;

    for (const auto& entry : old_table) {
        if (!entry.empty() && entry != "") {
            insert(entry);
        }
    }
}