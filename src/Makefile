# src/Makefile - builds direct client, static library, and shared library clients

CC      := gcc
AR      := ar
RANLIB  := ranlib
CFLAGS  := -Wall -Wextra -I../include
ifdef DEBUG
CFLAGS += -g -O0
else
CFLAGS += -O2
endif

SRCDIR   := .
OBJDIR   := ../obj
PICOBJDIR:= $(OBJDIR)/pic
BINDIR   := ../bin
LIBDIR   := ../lib

SOURCES := $(wildcard $(SRCDIR)/*.c)
# library sources: everything except main.c
LIB_SRCS := $(filter-out $(SRCDIR)/main.c,$(SOURCES))

# object files for direct build (one per source)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
# PIC objects used to build .so (only for lib sources)
PIC_OBJECTS := $(patsubst $(SRCDIR)/%.c,$(PICOBJDIR)/%.o,$(LIB_SRCS))

MAIN_OBJECT := $(OBJDIR)/main.o

TARGET        := $(BINDIR)/client
TARGET_STATIC := $(BINDIR)/client_static
TARGET_DYNAMIC:= $(BINDIR)/client_dynamic

LIB_A := $(LIBDIR)/libmyutils.a
LIB_SO:= $(LIBDIR)/libmyutils.so

.PHONY: all clean run run_static run_dynamic

all: $(TARGET) $(TARGET_STATIC) $(TARGET_DYNAMIC)

# Ensure directories exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(PICOBJDIR):
	mkdir -p $(PICOBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

# normal object compilation (for direct builds)
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# PIC object compilation (for building shared library)
$(PICOBJDIR)/%.o: $(SRCDIR)/%.c | $(PICOBJDIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# direct link: link all objects into bin/client
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# static library: archive PIC objects (ok to use PIC objects in .a)
$(LIB_A): $(PIC_OBJECTS) | $(LIBDIR)
	$(AR) rcs $(LIB_A) $(PIC_OBJECTS)
	$(RANLIB) $(LIB_A)

# shared library: link PIC objects into .so
$(LIB_SO): $(PIC_OBJECTS) | $(LIBDIR)
	$(CC) -shared -o $(LIB_SO) $(PIC_OBJECTS)

# static client: link main.o with static library
$(TARGET_STATIC): $(MAIN_OBJECT) $(LIB_A) | $(BINDIR)
	$(CC) $(CFLAGS) $(MAIN_OBJECT) $(LIB_A) -o $(TARGET_STATIC)

# dynamic client: link main.o against shared library (no rpath set here)
$(TARGET_DYNAMIC): $(MAIN_OBJECT) $(LIB_SO) | $(BINDIR)
	$(CC) $(CFLAGS) $(MAIN_OBJECT) -L$(LIBDIR) -lmyutils -o $(TARGET_DYNAMIC)

run: $(TARGET)
	./$(TARGET)

run_static: $(TARGET_STATIC)
	./$(TARGET_STATIC)

run_dynamic: $(TARGET_DYNAMIC)
	@echo "Note: you may need to set LD_LIBRARY_PATH to run this binary"
	./$(TARGET_DYNAMIC)

clean:
	rm -f $(OBJDIR)/*.o $(PICOBJDIR)/*.o $(TARGET) $(TARGET_STATIC) $(TARGET_DYNAMIC) $(LIB_A) $(LIB_SO)
