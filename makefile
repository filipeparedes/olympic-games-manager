# --- General configurations ---
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
TARGET = prog

# --- Automatic file discovery ---
# Find all .c files recursively within the src directory
SRCS = $(shell find src -name "*.c")

# Convert the list of .c files into a list of .o (object files)
OBJS = $(SRCS:.c=.o)

# --- Compilation rules ---

# Default rule: builds the final executable
all: $(TARGET)

# Linking step: combines object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Pattern rule: compiles each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Utility rules ---

# Debug mode: adds the -g flag for GDB/LLDB, cleans, and rebuilds everything
debug: CFLAGS += -g
debug: clean all

# Cleanup: removes the executable and deletes all .o files found in src
clean:
	rm -f $(TARGET)
	find src -name "*.o" -delete

# Prevent conflicts with files named 'all', 'debug', or 'clean'
.PHONY: all debug clean

# --- Execution rule ---
# Compiles (if necessary) and runs the program
run: all
	./$(TARGET)