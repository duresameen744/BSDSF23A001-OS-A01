# src/Makefile - compiles each .c into object files in ../obj
# and links them into ../bin/client

# --- Macros (variables) ---
CC      := gcc
CFLAGS  := -Wall -Wextra -I../include
# Add debugging flags by overriding when needed (make DEBUG=1)
ifdef DEBUG
CFLAGS += -g -O0
else
CFLAGS += -O2
endif

SRCDIR  := .
OBJDIR  := ../obj
BINDIR  := ../bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

TARGET  := $(BINDIR)/client

.PHONY: all clean run

# Default target
all: $(TARGET)

# Ensure directories exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Pattern rule: how to build each object from its C source
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link rule: link all objects into the final executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)
# Run the program
run: $(TARGET)
	./$(TARGET)

# Remove object files and the binary
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
