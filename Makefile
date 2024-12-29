# Makefile for University Management System

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -std=c++17

# List of source files
SRCS = Main.cpp \
       User.cpp \
       UserManager.cpp \
       login.cpp \
       generateAccount.cpp \
       Administrator.cpp \
       Professor.cpp \
       Student.cpp \
       Course.cpp \
       CourseManager.cpp

# Generate object file names by replacing .cpp with .o
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = university_management_system

# Default target
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to prevent conflicts with files named 'all' or 'clean'
.PHONY: all clean
