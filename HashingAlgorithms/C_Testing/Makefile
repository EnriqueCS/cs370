# Makefile for ChainingTest

# Compiler
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++11 -pthread -I/path/to/gtest/include

# Linker flags
LDFLAGS=-L/path/to/gtest/lib -lgtest -lgtest_main

# Source files
SOURCES=ChainingTest.cpp Chaining.cpp

# Object files
OBJECTS=$(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE=ChainingTest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean