# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2

# Source files
SRCS = assembler.c arena.c darray.c code-gen.c symbolTable.c lexical-scanner.c

# Executable name
TARGET = assembler

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean rule
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
