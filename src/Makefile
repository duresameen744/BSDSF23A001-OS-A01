# src/Makefile - builds both direct client and a static-library-based client (client_static)

CC      := gcc
AR      := ar
RANLIB  := ranlib
CFLAGS  := -Wall -Wextra -I../include
ifdef DEBUG
CFLAGS += -g -O0
else
CFLAGS += -O2
endif

SRCDIR  := .
OBJDIR  := ../obj
BINDIR  := ../bin
LIBDIR  := ../lib

SOURCES := $(wildcard $(SRCDIR)/*.c)
# library sources: everything except main.c
LIB_SRCS := $(filter-out $(SRCDIR)/main.c,$(SOURCES))
LIB_OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(LIB_SRCS))
MAIN_OBJECT := $(OBJDIR)/main.o

TARGET := $(BINDIR)/client
TARGET_STATIC := $(BINDIR)/client_static
LIB := $(LIBDIR)/libmyutils.a

.PHONY: all clean run run_static

all: $(TARGET) $(TARGET_STATIC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

# compile .c -> .o automatically
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# direct link (previous method) - links all objects directly
$(TARGET): $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES)) | $(BINDIR)
	$(CC) $(CFLAGS) $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES)) -o $(TARGET)

# create static library (archive the selected .o files)
$(LIB): $(LIB_OBJECTS) | $(LIBDIR)
	$(AR) rcs $(LIB) $(LIB_OBJECTS)
	$(RANLIB) $(LIB)

# build client_static by linking main.o with the static library
$(TARGET_STATIC): $(MAIN_OBJECT) $(LIB) | $(BINDIR)
	$(CC) $(CFLAGS) $(MAIN_OBJECT) $(LIB) -o $(TARGET_STATIC)

run: $(TARGET)
	./$(TARGET)

run_static: $(TARGET_STATIC)
	./$(TARGET_STATIC)

clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(TARGET_STATIC) $(LIB)
