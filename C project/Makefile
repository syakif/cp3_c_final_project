# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -I.

# Source files
SRCS = main.c file_ops.c material.c train.c utils.c vagon.c

# Header files
HEADERS = file_ops.h material.h train.h utils.h vagon.h

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = main.exe

# Default rule
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compiling source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
