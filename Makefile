CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -g -fopenmp -O3 
INC_DIR = include
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
BIN_DIR = bin

# Find all the .cpp files in src, test, and their subdirectories
SRC_FILES := $(shell find $(SRC_DIR) $(TEST_DIR) -type f -name '*.cpp')

# Generate the list of corresponding object files
OBJ_FILES := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SRC_FILES)))

# Add main.cpp to the list of source files
SRC_FILES += test/main.cpp

# Name of the executable
EXECUTABLE = $(BIN_DIR)/main

# Main rule to build the executable
all: $(EXECUTABLE)

# Rule to create build and bin directories if necessary
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Rule to compile each .cpp file into a .o file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Rule to build the executable using the object files
$(EXECUTABLE): $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to clean the intermediate files and the executable
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Rule to run the program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run
