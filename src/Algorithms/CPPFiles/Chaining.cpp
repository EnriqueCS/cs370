#include "../HashingAlgorithm.h"

void Chaining::insert(const std::string& key) {
    size_t i = hash_function(key);
    auto node = std::make_shared<Node>(key);
    if (hash_table[i] != nullptr) {
        node->next = hash_table[i];
    }
    hash_table[i] = node;
}

void Chaining::remove(const std::string& key) {
    size_t i = hash_function(key);
    std::shared_ptr<Node> current = hash_table[i], prev = nullptr;

    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    // Remove the first node
    if (prev == nullptr) {
        hash_table[i] = current->next;  
    } else {
        prev->next = current->next;
    }
}

bool Chaining::search(const std::string& key) {
    size_t i = hash_function(key);
    std::shared_ptr<Node> current = hash_table[i];

    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }

    return false;
}