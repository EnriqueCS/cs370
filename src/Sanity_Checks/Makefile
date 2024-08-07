# Makefile for Hashing Tests

# Compiler
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++17 -pthread -I../../googletest/googletest/include -I/usr/local/include

# Linker flags
LDFLAGS=-L../../googletest/googletest/lib -L/usr/local/lib -lgtest -lgtest_main -lpapi

# Source files for ChainingTest
SOURCES_CHAINING=test_chaining.cpp ../Algorithms/Chaining.cpp

# Source files for CuckooHashingTest
SOURCES_CUCKOO=test_cuckoo_hashing.cpp ../Algorithms/CuckooHashing.cpp

# Source files for OpenAddressingTest
SOURCES_OPEN_ADDRESSING=test_open_addressing.cpp ../Algorithms/OpenAddressing.cpp

# Object files for ChainingTest
OBJECTS_CHAINING=$(SOURCES_CHAINING:.cpp=.o)

# Object files for CuckooHashingTest
OBJECTS_CUCKOO=$(SOURCES_CUCKOO:.cpp=.o)

# Object files for OpenAddressingTest
OBJECTS_OPEN_ADDRESSING=$(SOURCES_OPEN_ADDRESSING:.cpp=.o)

# Executable names
EXECUTABLE_CHAINING=../Executables/ChainingTest
EXECUTABLE_CUCKOO=../Executables/CuckooHashingTest
EXECUTABLE_OPEN_ADDRESSING=../Executables/OpenAddressingTest

# Default target
all: $(EXECUTABLE_CHAINING) $(EXECUTABLE_CUCKOO) $(EXECUTABLE_OPEN_ADDRESSING)

$(EXECUTABLE_CHAINING): $(OBJECTS_CHAINING)
	$(CXX) $(CXXFLAGS) $(OBJECTS_CHAINING) -o $@ $(LDFLAGS)

$(EXECUTABLE_CUCKOO): $(OBJECTS_CUCKOO)
	$(CXX) $(CXXFLAGS) $(OBJECTS_CUCKOO) -o $@ $(LDFLAGS)

$(EXECUTABLE_OPEN_ADDRESSING): $(OBJECTS_OPEN_ADDRESSING)
	$(CXX) $(CXXFLAGS) $(OBJECTS_OPEN_ADDRESSING) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJECTS_CHAINING) $(OBJECTS_CUCKOO) $(OBJECTS_OPEN_ADDRESSING) $(EXECUTABLE_CHAINING) $(EXECUTABLE_CUCKOO) $(EXECUTABLE_OPEN_ADDRESSING)

.PHONY: all clean
