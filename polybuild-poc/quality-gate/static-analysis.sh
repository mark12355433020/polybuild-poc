#!/bin/bash
# Static Analysis Quality Gate
# Zero-tolerance for memory leaks and undefined behavior

run_static_analysis() {
    local source_dir="$1"
    local violations=0
    
    echo "Running static analysis on: $source_dir"
    
    # Clang-tidy analysis
    if command -v clang-tidy &> /dev/null; then
        echo "Running clang-tidy..."
        if ! find "$source_dir" -name "*.c" -exec clang-tidy {} \; --checks=clang-analyzer-* --warnings-as-errors; then
            echo "VIOLATION: Static analysis warnings detected"
            ((violations++))
        fi
    fi
    
    # Cppcheck analysis (if available)
    if command -v cppcheck &> /dev/null; then
        echo "Running cppcheck..."
        if ! cppcheck --error-exitcode=1 --enable=all "$source_dir" 2>/dev/null; then
            echo "VIOLATION: Cppcheck warnings detected"
            ((violations++))
        fi
    fi
    
    return $violations
}

# Execute if called directly
if [ "${BASH_SOURCE[0]}" == "${0}" ]; then
    if [ "$#" -eq 0 ]; then
        echo "Usage: $0 <source_directory>"
        exit 1
    fi
    
    run_static_analysis "$1"
    exit $?
fi
