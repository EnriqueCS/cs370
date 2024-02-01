
# Hashing Algorithms Project

This project implements three distinct hashing algorithms: Open Addressing, Chaining, and Cuckoo Hashing. Each algorithm offers a unique method for handling collisions within a hash table, showcasing different strategies for inserting, searching, and deleting keys in a hash-based data structure.

## Directory Structure

- **HashingAlgorithms/** - Root directory of the project.
- **Algorithms/** - Contains the implementation of the hashing algorithms.
  - **Chaining.py** - Implements the Chaining method for collision resolution. This script defines a hash table where collisions are handled by linking colliding elements into a linked list at the corresponding index.
  - **OpenAddressing.py** - Implements the Open Addressing strategy for collision resolution, including methods like linear probing, quadratic probing, or double hashing to find the next available slot.
  - **CuckooHashing.py** - Implements the Cuckoo Hashing method, a high-performance collision resolution strategy using multiple hash functions and relocating keys to resolve collisions.
- **Runner.py** - A script to run demonstrations or tests for each hashing algorithm implemented, providing an interface to interact with the hash tables and observe their behavior.
- **Testing.py** - Contains unit tests for each hashing algorithm implementation, ensuring correctness and performance of the collision resolution strategies.

## Usage

To use the hashing algorithms, run the `Runner.py` script. This script allows you to select an algorithm, perform operations like insertions, deletions, and searches, and observe the outcome. It serves as a practical demonstration of how each hashing technique handles collisions and manages data.

For testing and validation, execute `Testing.py` to run predefined test cases on each algorithm, ensuring they operate as expected.

## Requirements

- Python 3.x

Ensure Python 3.x is installed on your system to run the scripts. No additional libraries are required for the basic functionality of these algorithms.
