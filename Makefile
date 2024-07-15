
# Makefile for C++ project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source files directory
SRCDIR = src

# Output directory
OUTDIR = bin

# List of source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# List of object files (automatically generated from source files)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OUTDIR)/%.o, $(SRCS))

# Target executable
TARGET = myprogram

# Default target
all: $(TARGET)

# Linking object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/$@ $^

# Compiling each source file into an object file
$(OUTDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean build artifacts
clean:
	rm -f $(OUTDIR)/*.o $(OUTDIR)/$(TARGET)
