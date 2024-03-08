# Makefile for Hashing Tests

# Compiler
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++17 -pthread -I/usr/include

# Linker flags
LDFLAGS=-lpapi -pthread

# Source files
SOURCES=./TestingLib/papi_metrics.cpp ./papi_runner.cpp \
        ../Algorithms/Chaining.cpp ../Algorithms/CuckooHashing.cpp ../Algorithms/OpenAddressing.cpp

# Object files
OBJECTS=$(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE=../Executables/PapiTest

# Default target
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean