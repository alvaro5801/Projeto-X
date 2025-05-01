# Makefile para o Projeto-X

# Variáveis
CC = gcc
CFLAGS = -Wall -g
INCLUDE_DIR = include
BUILD_DIR = build
SRC_DIR = src
TARGET = $(BUILD_DIR)/testes

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
INCLUDES = -I$(INCLUDE_DIR)   # Caminho para os includes

# Regras

# Regra principal: Compila tudo e cria o executável
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR) # Cria o diretório build/ se não existir
	$(CC) $(OBJS) -o $@

# Regra para compilar arquivos .c para .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR) # Garante que o diretório build exista
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -rf $(BUILD_DIR)/*
	@echo "Arquivos de build limpos."

# Phony targets (alvos que não representam arquivos)
.PHONY: all clean
