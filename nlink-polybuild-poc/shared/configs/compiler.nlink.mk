# Shared compiler configuration for NLink components
# Include this in component Makefiles

CC = gcc
CFLAGS_COMMON = -std=c99 -Wall -Wextra -Wpedantic -Werror
CFLAGS_COMMON += -I../shared/headers
CFLAGS_COMMON += -DNLINK_ORCHESTRATION=1
CFLAGS_COMMON += -DSINPHASE_GOVERNANCE=1

# Optimization levels
CFLAGS_DEBUG = $(CFLAGS_COMMON) -g -O0 -DDEBUG
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O3 -DNDEBUG

# Use release by default
CFLAGS ?= $(CFLAGS_RELEASE)
