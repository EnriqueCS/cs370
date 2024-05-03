# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# Source directory
SRCDIR = CPPFiles

# Object files directory
OBJDIR = obj

# Binary directory
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Include directories
INCLUDES = -I.

# Test code source file
TESTSRC = TestCode.cpp

# Target executable
TARGET = $(BINDIR)/test

# Make sure the binary directory exists
$(shell mkdir -p $(BINDIR))
$(shell mkdir -p $(OBJDIR))

# Default target
all: $(TARGET)

# Link the test executable
$(TARGET): $(OBJECTS) $(TESTSRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJECTS) $(TESTSRC)

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean target for cleaning up the compiled files
clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/$(TARGET)

# PHONY targets are not files
.PHONY: all clean
