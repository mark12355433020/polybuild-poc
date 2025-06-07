COMPONENT_NAME = polybuild_core
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIR = ../artifacts
TARGET = $(LIBDIR)/lib$(COMPONENT_NAME).a

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CFLAGS = -std=c99 -O3 -Wall -Wextra -Wpedantic -Werror
CFLAGS += -I$(INCDIR) -I../shared/headers

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(LIBDIR)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)
