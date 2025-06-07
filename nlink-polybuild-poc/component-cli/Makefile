# PolyBuild CLI Component Makefile

COMPONENT_NAME = polybuild
VERSION = 1.0.0

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = ../artifacts

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/$(COMPONENT_NAME)

# Link with all component libraries
LIBS = -L../artifacts -lpolybuild_resolver -lpolybuild_orchestrator -lpolybuild_core
LIBS += -pthread -lm

CFLAGS = -std=c99 -O2 -Wall -Wextra -Wpedantic -Werror
CFLAGS += -I$(INCDIR) -I../shared/headers
CFLAGS += -I../component-resolver/include -I../component-orchestrator/include

.PHONY: all clean nlink-validate

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BINDIR)
	@echo "[NLINK] Linking executable: $(TARGET)"
	$(CC) $(OBJECTS) $(LIBS) -o $@
	@echo "[NLINK] PolyBuild CLI built successfully"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "[NLINK] Compiling CLI: $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

nlink-validate:
	@echo "[NLINK] Validating CLI configuration"
	@test -f nlink.txt && echo "[NLINK] CLI configuration valid"
