# PolyBuild CLI Executable

add_executable(polybuild
    src/main.c
)

target_link_libraries(polybuild 
    polybuild-core
    ${LINKER_DEPENDENCIES}
)

# Install CLI executable
install(TARGETS polybuild
    RUNTIME DESTINATION bin
)
