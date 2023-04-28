
CC = gcc
CFLAGS = 
SRC_DIR = ./
OBJ_DIR = ../obj/
BIN_DIR = ../executables/

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SOURCES))

.PHONY: all clean

all: $(EXECUTABLES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLES)
