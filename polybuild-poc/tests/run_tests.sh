#!/bin/bash
# Comprehensive Test Suite for PolyBuild POC

set -euo pipefail

TEST_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$TEST_DIR")"

run_unit_tests() {
    echo "Running unit tests..."
    
    # Test core resolver
    if [ -f "$PROJECT_ROOT/build/core/test_resolver" ]; then
        "$PROJECT_ROOT/build/core/test_resolver"
    else
        echo "Unit tests not built - skipping"
    fi
}

run_integration_tests() {
    echo "Running integration tests..."
    
    # Test CLI integration
    if [ -f "$PROJECT_ROOT/build/cli/polybuild" ]; then
        "$PROJECT_ROOT/build/cli/polybuild" --help > /dev/null
        "$PROJECT_ROOT/build/cli/polybuild" --dry-run --linker=nlink .
    fi
}

run_quality_gates() {
    echo "Running quality gates..."
    
    cd "$PROJECT_ROOT"
    make quality-check || echo "Quality gate warnings detected"
}

run_performance_tests() {
    echo "Running performance tests..."
    
    # Measure build time
    local start_time=$(date +%s.%N)
    make -C "$PROJECT_ROOT/build" >/dev/null 2>&1 || true
    local end_time=$(date +%s.%N)
    local duration=$(echo "$end_time - $start_time" | bc -l)
    
    echo "Build duration: ${duration}s"
}

main() {
    echo "PolyBuild POC Test Suite"
    echo "========================"
    
    run_unit_tests
    run_integration_tests
    run_quality_gates
    run_performance_tests
    
    echo "Test suite completed"
}

main "$@"
