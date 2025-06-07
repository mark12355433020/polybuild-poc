# PolyBuild Resolver Component Makefile
# NLink Orchestration Integration

COMPONENT_NAME = polybuild_resolver
VERSION = 2.1.0

# Include shared NLink configuration
include ../shared/configs/compiler.nlink.mk

# Component-specific settings
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIR = ../artifacts

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(LIBDIR)/lib$(COMPONENT_NAME).a

# Compiler flags from NLink configuration
CFLAGS = -std=c99 -O3 -Wall -Wextra -Wpedantic -Werror
CFLAGS += -I$(INCDIR) -I../shared/headers
CFLAGS += -DCOMPONENT_NAME=\"$(COMPONENT_NAME)\"
CFLAGS += -DCOMPONENT_VERSION=\"$(VERSION)\"

# Build targets
.PHONY: all clean test nlink-validate

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(LIBDIR)
	@echo "[NLINK] Creating library: $(TARGET)"
	ar rcs $@ $^
	@echo "[NLINK] Component $(COMPONENT_NAME) built successfully"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "[NLINK] Compiling: $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "[NLINK] Component $(COMPONENT_NAME) cleaned"

test:
	@echo "[NLINK] Running component tests for $(COMPONENT_NAME)"
	# Test framework integration here

nlink-validate:
	@echo "[NLINK] Validating component configuration"
	@if [ -f nlink.txt ]; then \
		echo "[NLINK] Component configuration found: nlink.txt"; \
	else \
		echo "[NLINK] ERROR: Missing component configuration"; \
		exit 1; \
	fi

# NLink cost function monitoring
cost-check:
	@echo "[NLINK] Checking component cost function"
	@wc -l src/*.c | tail -n1 | awk '{if($$1 > 200) print "[NLINK] WARNING: High complexity detected"; else print "[NLINK] Cost function within threshold"}'
