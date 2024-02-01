from hashing_algorithm import HashingAlgorithm

class CuckooHashing(HashingAlgorithm):
    def __init__(self, table_size=10):
        self.table_size = table_size  # Example size
        self.hash_table1 = [None] * self.table_size
        self.hash_table2 = [None] * self.table_size
    
    def insert(self, key, value):
        pos1 = self._hash_function1(key)
        if self.hash_table1[pos1] is None:
            self.hash_table1[pos1] = (key, value)
            return
        else:
            pos2 = self._hash_function2(key)
            if self.hash_table2[pos2] is None:
                self.hash_table2[pos2] = (key, value)
                return
            else:
                # Handle the case where both positions are occupied,
                # which may involve rehashing or moving existing keys.
                pass
    
    def delete(self, key):
        pos1 = self._hash_function1(key)
        if self.hash_table1[pos1] and self.hash_table1[pos1][0] == key:
            self.hash_table1[pos1] = None
            return True
        pos2 = self._hash_function2(key)
        if self.hash_table2[pos2] and self.hash_table2[pos2][0] == key:
            self.hash_table2[pos2] = None
            return True
        return False  # Key not found
    
    def search(self, key):
        pos1 = self._hash_function1(key)
        if self.hash_table1[pos1] and self.hash_table1[pos1][0] == key:
            return self.hash_table1[pos1][1]
        pos2 = self._hash_function2(key)
        if self.hash_table2[pos2] and self.hash_table2[pos2][0] == key:
            return self.hash_table2[pos2][1]
        return None  # Key not found
    
    def _hash_function1(self, key):
        # Simple hash function for demonstration
        return hash(key) % self.table_size
    
    def _hash_function2(self, key):
        # An alternative hash function for demonstration
        return (hash(key) + 1) % self.table_size