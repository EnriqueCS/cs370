#include <vector>
#include <optional>
#include <string>
#include <utility> // For std::pair

class OpenAddressing : public HashingAlgorithm {
private:
    std::vector<std::optional<std::pair<std::string, std::string>>> hash_table;
    size_t table_size;
    size_t count; // To keep track of the number of elements in the hash table

    size_t _hash_function(const std::string& key) const {
        std::hash<std::string> hash_fn;
        return hash_fn(key) % table_size;
    }

public:
    OpenAddressing(size_t table_size = 10) 
        : table_size(table_size), hash_table(table_size), count(0) {}

    void insert(const std::string& key, const std::string& value) override {
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

    void remove(const std::string& key) override {
        size_t index = _hash_function(key);
        for (size_t i = 0; i < table_size; ++i) {
            size_t probe_index = (index + i) % table_size;
            if (hash_table[probe_index] && hash_table[probe_index]->first == key) {
                hash_table[probe_index].reset();
                --count;
                return;
            }
            if (!hash_table[probe_index]) { // Stop if an empty slot is found
                return;
            }
        }
    }

    std::string search(const std::string& key) override {
        size_t index = _hash_function(key);
        for (size_t i = 0; i < table_size; ++i) {
            size_t probe_index = (index + i) % table_size;
            if (hash_table[probe_index] && hash_table[probe_index]->first == key) {
                return hash_table[probe_index]->second;
            }
            if (!hash_table[probe_index]) { // Stop if an empty slot is found
                break;
            }
        }
        throw std::logic_error("Key not found");
    }
};
