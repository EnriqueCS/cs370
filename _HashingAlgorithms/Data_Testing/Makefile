# Makefile for Hashing Tests

# Compiler
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++17 -pthread -I/workspaces/cs-370/googletest/googletest/include

# Assuming the Google Test libraries are in the following path; adjust if necessary
LDFLAGS=-L/workspaces/cs-370/googletest/googletest/lib -lgtest -lgtest_main

# Source files for ChainingTest
SOURCES=HashTableTests.cpp ../C_Algorithms/Chaining.cpp ../C_Algorithms/CuckooHashing.cpp ../C_Algorithms/OpenAddressing.cpp

# Object files for ChainingTest
OBJECTS=$(SOURCES:.cpp=.o)

# Executable names
DICTIONARY_TEST=../Executables/TestDictionary

# Default target
all: $(DICTIONARY_TEST)

$(DICTIONARY_TEST): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(DICTIONARY_TEST)

.PHONY: all clean