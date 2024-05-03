#include "../HashingAlgorithm.h"
#include <vector>
#include <string>
#include <stdexcept>

size_t CuckooHashing::hash_function2(const std::string& value) const {
    std::hash<std::string> hasher;
    return (hasher(value) / table_size) % table_size;
}

void CuckooHashing::insert(const std::string& value) {
    if (search(value)) return;

    std::string temp = value;
    for (int i = 0; i < LIMIT; ++i) {
        size_t j = hash_function(temp);
        if (T_1[j].empty()) {
            T_1[j] = temp;
            return;
        }
        std::swap(temp, T_1[j]);

        j = hash_function2(temp);
        if (T_2[j].empty()) {
            T_2[j] = temp;
            return;
        }
        std::swap(temp, T_2[j]);
    }

    rehash();
    insert(value);
}

// Cuckoo Hashing remove function
void CuckooHashing::remove(const std::string& value) {
    if (!search(value)) return;

    size_t j = hash_function(value);
    if (T_1[j] == value) {
        T_1[j].clear();
        return;
    }

    j = hash_function2(value);
    if (T_2[j] == value) {
        T_2[j].clear();
        return;
    }
}

bool CuckooHashing::search(const std::string& value) {
    size_t j = hash_function(value);
    if (T_1[j] == value) return true;

    j = hash_function2(value);
    if (T_2[j] == value) return true;

    return false;
}

// Cuckoo Hashing rehash function: NOT IN USE
void CuckooHashing::rehash() {
    // size_t old_size = table_size;
    table_size *= 2;
    std::vector<std::string> old_T_1 = T_1, old_T_2 = T_2;

    T_1.clear(); T_1.resize(table_size, "");
    T_2.clear(); T_2.resize(table_size, "");

    for (const std::string& value : old_T_1) {
        if (!value.empty()) insert(value);
    }
    for (const std::string& value : old_T_2) {
        if (!value.empty()) insert(value);
    }
}