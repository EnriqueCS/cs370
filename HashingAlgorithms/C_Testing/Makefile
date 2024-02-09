# Makefile for ChainingTest

# Compiler
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++14 -pthread -I/workspaces/cs-370/googletest/googletest/include

# Assuming the Google Test libraries are in the following path; adjust if necessary
LDFLAGS=-L/workspaces/cs-370/googletest/googletest/lib -lgtest -lgtest_main

# Source files
SOURCES=test_chaining.cpp ../C_Algorithms/Chaining.cpp

# Object files
OBJECTS=$(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE=../Executables/ChainingTest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean