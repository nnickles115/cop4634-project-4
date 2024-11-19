# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall -std=c++11 -O0 -Wno-unused-but-set-variable

# Ouput file
TARGET = matrix

# Source files
SOURCES = *.cpp

# Object files
OBJECTS = $(SOURCES:.cpp = .o)

# Compile rule (make)
all: $(TARGET)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files and make binary
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Clean rule
clean:
	rm -f *.o $(TARGET)