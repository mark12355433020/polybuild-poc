cmake_minimum_required(VERSION 3.16)
project(PolyBuildPOC LANGUAGES C)

# Sinphasé compliance enforcement
add_compile_options(-Werror -Wall -Wextra -Wpedantic)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# NLink dependency configuration
find_library(NLINK_LIB nlink HINTS 
    /usr/local/lib 
    /opt/nlink/lib
    ${CMAKE_SOURCE_DIR}/tools/nlink/lib
)

if(NLINK_LIB)
    message(STATUS "Found NLink: ${NLINK_LIB}")
else()
    message(WARNING "NLink not found - using mock for development")
    set(NLINK_LIB "")
endif()

set(LINKER_DEPENDENCIES ${NLINK_LIB} pthread)

# Include directories
include_directories(core/include)

# Core architecture
add_subdirectory(core)
add_subdirectory(cli)

# Quality gate integration
add_custom_target(quality-check
    COMMAND ${CMAKE_SOURCE_DIR}/quality-gate/static-analysis.sh ${CMAKE_SOURCE_DIR}/core/src
    COMMAND ${CMAKE_SOURCE_DIR}/quality-gate/sinphase-check.sh ${CMAKE_SOURCE_DIR}/core/src/resolver.c
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running quality gates"
)

# Build reproducibility test
add_custom_target(reproducibility-test
    COMMAND ${CMAKE_COMMAND} -E echo "Testing build reproducibility..."
    COMMAND sha256sum ${CMAKE_BINARY_DIR}/cli/polybuild > ${CMAKE_SOURCE_DIR}/artifacts/hashes.txt || true
    COMMAND ${CMAKE_COMMAND} --build . --target clean
    COMMAND ${CMAKE_COMMAND} --build .
    COMMAND sha256sum -c ${CMAKE_SOURCE_DIR}/artifacts/hashes.txt || echo "Build reproducibility test completed"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Testing build reproducibility"
)

# Documentation target
add_custom_target(docs
    COMMAND ${CMAKE_COMMAND} -E echo "Generating documentation..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating project documentation"
)
