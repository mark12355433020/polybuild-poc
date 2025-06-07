# PolyBuild Orchestrator Component Makefile

COMPONENT_NAME = polybuild_orchestrator
VERSION = 1.5.0

SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIR = ../artifacts

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(LIBDIR)/lib$(COMPONENT_NAME).a

CFLAGS = -std=c99 -O3 -Wall -Wextra -Wpedantic -Werror
CFLAGS += -I$(INCDIR) -I../shared/headers -I../component-resolver/include
CFLAGS += -DCOMPONENT_NAME=\"$(COMPONENT_NAME)\"

.PHONY: all clean nlink-validate

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(LIBDIR)
	@echo "[NLINK] Creating orchestrator library: $(TARGET)"
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "[NLINK] Compiling orchestrator: $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

nlink-validate:
	@echo "[NLINK] Validating orchestrator configuration"
	@test -f nlink.txt && echo "[NLINK] Configuration valid" || echo "[NLINK] Missing nlink.txt"
