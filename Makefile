# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Directories
SRC_DIR = src
LIB_DIR = $(SRC_DIR)/dependencies
BUILD_DIR = build

# Source files
SRC = $(SRC_DIR)/main.c $(LIB_DIR)/default_lib/default_funcs.c $(LIB_DIR)/filetree_lib/filetree_funcs.c

# Output executable
OUT = $(BUILD_DIR)/spit

# Default target
all: $(BUILD_DIR) $(OUT)

# Rule to create the build directory
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Rule to build the executable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Clean up build files
clean:
	rm -f $(OUT)

# Phony targets
.PHONY: all clean