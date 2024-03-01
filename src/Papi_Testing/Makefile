# Makefile for Hashing Tests

# Compiler
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++17 -pthread -I../../googletest/googletest/include -I/usr/local/include

# Linker flags
LDFLAGS=-L../../googletest/googletest/lib -L/usr/local/lib -lgtest -lgtest_main -lpapi -pthread

# Source files
SOURCES=./papi_metrics.cpp ./papi_runner.cpp \
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