CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -g -fopenmp -O3 
INC_DIR = include
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Encontre todos os arquivos .cpp em src e suas subpastas
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp')

# Gere a lista de objetos correspondentes
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Nome do executável
EXECUTABLE = $(BIN_DIR)/main

# Regra principal para construir o executável
all: $(EXECUTABLE)

# Regra para criar diretórios de compilação e binários, se necessário
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regra para compilar cada arquivo .cpp em um arquivo .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Adicione seu main.cpp como dependência aqui
$(BUILD_DIR)/main.o: main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Regra para construir o executável usando os objetos
$(EXECUTABLE): $(OBJ_FILES) $(BUILD_DIR)/main.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para limpar os arquivos intermediários e o executável
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Regra para rodar o programa
run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run
