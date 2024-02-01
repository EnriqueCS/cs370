import unittest
from chaining import Chaining

class TestCuckooHashing(unittest.TestCase):
    def setUp(self):
        self.hash_table = Chaining()

    def test_insert_search(self):
        self.hash_table.insert("key1", "value1")
        self.assertEqual(self.hash_table.search("key1"), "value1", "Should return the correct value for 'key1'")

    def test_delete(self):
        self.hash_table.insert("key2", "value2")
        self.hash_table.delete("key2")
        self.assertIsNone(self.hash_table.search("key2"), "Should return None for deleted key")

if __name__ == '__main__':
    unittest.main()