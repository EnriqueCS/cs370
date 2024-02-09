#include <stdexcept> // For std::logic_error
#include <string>    // Assuming keys and values are strings for simplicity

class HashingAlgorithm {
public:
    virtual ~HashingAlgorithm() {} // Virtual destructor to allow for proper cleanup of derived classes

    // Insert a key-value pair into the hash table
    virtual void insert(const std::string& key, const std::string& value) = 0;

    // Delete a key-value pair from the hash table
    virtual void remove(const std::string& key) = 0;

    // Search for a key in the hash table and return its value
    virtual std::string search(const std::string& key) = 0;
};