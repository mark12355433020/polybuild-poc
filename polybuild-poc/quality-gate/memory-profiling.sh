#!/bin/bash
# Memory Safety Quality Gate
# Valgrind integration for leak detection

run_memory_analysis() {
    local executable="$1"
    local test_args="${2:-}"
    
    echo "Running memory analysis on: $executable"
    
    if ! command -v valgrind &> /dev/null; then
        echo "WARNING: Valgrind not available - skipping memory analysis"
        return 0
    fi
    
    # Run valgrind with strict settings
    local valgrind_output=$(mktemp)
    if valgrind --leak-check=full --error-exitcode=1 --track-origins=yes \
               --log-file="$valgrind_output" "$executable" $test_args 2>/dev/null; then
        echo "SUCCESS: No memory leaks detected"
        rm -f "$valgrind_output"
        return 0
    else
        echo "VIOLATION: Memory issues detected"
        echo "Valgrind output:"
        cat "$valgrind_output"
        rm -f "$valgrind_output"
        return 1
    fi
}

# Execute if called directly
if [ "${BASH_SOURCE[0]}" == "${0}" ]; then
    if [ "$#" -eq 0 ]; then
        echo "Usage: $0 <executable> [test_args]"
        exit 1
    fi
    
    run_memory_analysis "$@"
    exit $?
fi
