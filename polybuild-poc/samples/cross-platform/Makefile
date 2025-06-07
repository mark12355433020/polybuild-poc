# Cross-Platform Build Demo
# Shows PolyBuild working across different environments

CC ?= gcc
CFLAGS = -Wall -Wextra -I../../core/include
LDFLAGS = -L../../build/core -lpolybuild-core

SOURCES = demo.c
TARGET = cross-platform-demo

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
