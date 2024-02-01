class HashingAlgorithm:
    def insert(self, key, value):
        """Insert a key-value pair into the hash table."""
        raise NotImplementedError("This method should be overridden by subclasses.")

    def delete(self, key):
        """Delete a key-value pair from the hash table."""
        raise NotImplementedError("This method should be overridden by subclasses.")

    def search(self, key):
        """Search for a key in the hash table and return its value."""
        raise NotImplementedError("This method should be overridden by subclasses.")