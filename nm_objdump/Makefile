# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g3

# Target executable
TARGET = hnm

# Source files: includes all .c files in the directory
SRC = $(wildcard *.c)

# Rule to build the target executable directly from source files
$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up the executable
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: clean
