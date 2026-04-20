# --- General configurations ---
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
TARGET = prog

# Directories
SRC_DIR = src
BUILD_DIR = build

# --- Automatic file discovery ---
# Find all .c files recursively
SRCS = $(shell find $(SRC_DIR) -name "*.c")

# Convert src/path/file.c to build/path/file.o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# --- Compilation rules ---

all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Pattern rule: compiles each .c into the build directory
# The 'mkdir' ensures the subdirectories exist before compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Utility rules ---

debug: CFLAGS += -g
debug: clean all

# Cleanup
clean:
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR)

.PHONY: all debug clean run

run: all
	./$(TARGET)