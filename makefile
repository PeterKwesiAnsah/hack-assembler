# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -O2

# Source files
SRCS = tokenizer.c parser.c symbolTable.c assembler.c scanner.c code.c

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
