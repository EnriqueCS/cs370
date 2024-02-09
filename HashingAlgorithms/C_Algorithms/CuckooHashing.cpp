#include <vector>
#include <utility> // For std::pair
#include <string>
#include <optional>

class CuckooHashing : public HashingAlgorithm {
private:
    std::vector<std::optional<std::pair<std::string, std::string>>> hash_table1, hash_table2;
    size_t table_size;

    size_t _hash_function1(const std::string& key) const {
        std::hash<std::string> hash_fn;
        return hash_fn(key) % table_size;
    }

    size_t _hash_function2(const std::string& key) const {
        std::hash<std::string> hash_fn;
        return (hash_fn(key) + 1) % table_size;
    }

public:
    CuckooHashing(size_t table_size = 10) 
        : table_size(table_size), 
          hash_table1(table_size), 
          hash_table2(table_size) {}

    void insert(const std::string& key, const std::string& value) override {
        size_t pos1 = _hash_function1(key);
        if (!hash_table1[pos1]) {
            hash_table1[pos1] = std::make_pair(key, value);
            return;
        } else {
            size_t pos2 = _hash_function2(key);
            if (!hash_table2[pos2]) {
                hash_table2[pos2] = std::make_pair(key, value);
                return;
            } else {
                // Handle the case where both positions are occupied,
                // which may involve rehashing or moving existing keys.
                // This is a simplified placeholder and does not implement
                // the full cuckoo hashing algorithm's displacement logic.
            }
        }
    }

    void remove(const std::string& key) override {
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
        // If key not found, no action is performed.
    }

    std::string search(const std::string& key) override {
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
};