from hashing_algorithm import HashingAlgorithm

class OpenAddressing(HashingAlgorithm):
    def __init__(self, table_size=10):
        self.table_size = table_size
        self.hash_table = [None] * self.table_size
        self.count = 0  # To keep track of the number of elements in the hash table
    
    def insert(self, key, value):
        if self.count == self.table_size:
            return "Hash Table is full"
        index = self._hash_function(key)
        for i in range(self.table_size):
            # Attempt to find a slot using a probing method
            probe_index = (index + i) % self.table_size
            if not self.hash_table[probe_index]:
                self.hash_table[probe_index] = (key, value)
                self.count += 1
                return
            # If the key already exists, update the value
            if self.hash_table[probe_index][0] == key:
                self.hash_table[probe_index] = (key, value)
                return
    
    def delete(self, key):
        index = self._hash_function(key)
        for i in range(self.table_size):
            probe_index = (index + i) % self.table_size
            if self.hash_table[probe_index] and self.hash_table[probe_index][0] == key:
                self.hash_table[probe_index] = None
                self.count -= 1
                return True
            if not self.hash_table[probe_index]:  # Stop if an empty slot is found
                return False
        return False  # Key not found
    
    def search(self, key):
        index = self._hash_function(key)
        for i in range(self.table_size):
            probe_index = (index + i) % self.table_size
            if self.hash_table[probe_index] and self.hash_table[probe_index][0] == key:
                return self.hash_table[probe_index][1]
            if not self.hash_table[probe_index]:  # Stop if an empty slot is found
                return None
        return None  # Key not found
    
    def _hash_function(self, key):
        # Simple hash function for demonstration
        return hash(key) % self.table_size