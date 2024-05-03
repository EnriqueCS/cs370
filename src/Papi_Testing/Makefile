# Makefile for Hashing Tests
# Compiler
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++17 -pthread -I/usr/include

# Linker flags
LDFLAGS=-lpapi -pthread

# Source files
SOURCES=./papi_runner.cpp \
		./TestingLib/CPPFiles/func_tester.cpp \
		./TestingLib/CPPFiles/func_testerT.cpp \
		./TestingLib/CPPFiles/counter_manager.cpp \
		./Util/papi_log.cpp \
        ../Algorithms/CPPFiles/Chaining.cpp \
		../Algorithms/CPPFiles/CuckooHashing.cpp \
		../Algorithms/CPPFiles/OpenAddressing.cpp

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
	rm -rf ../Papi_Results

run-papi:
	../Executables/PapiTest

.PHONY: all clean