from hashing_algorithm import HashingAlgorithm

class Chaining(HashingAlgorithm):
    def __init__(self, table_size=10):
        self.table_size = table_size  # Example size
        self.hash_table = [[] for _ in range(self.table_size)]
    
    def insert(self, key, value):
        index = self._hash_function(key)
        # Check for existing key and update
        for i, (k, v) in enumerate(self.hash_table[index]):
            if k == key:
                self.hash_table[index][i] = (key, value)
                return
        # Otherwise, append new key-value pair
        self.hash_table[index].append((key, value))
    
    def delete(self, key):
        index = self._hash_function(key)
        for i, (k, v) in enumerate(self.hash_table[index]):
            if k == key:
                del self.hash_table[index][i]
                return True
        return False  # Key not found
    
    def search(self, key):
        index = self._hash_function(key)
        for k, v in self.hash_table[index]:
            if k == key:
                return v
        return None  # Key not found
    
    def _hash_function(self, key):
        # Simple hash function for demonstration
        return hash(key) % self.table_size
