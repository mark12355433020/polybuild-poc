# PolyBuild Core Library

add_library(polybuild-core
    src/resolver.c
    src/composer.c
)

target_include_directories(polybuild-core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(polybuild-core ${LINKER_DEPENDENCIES})

# Install targets
install(TARGETS polybuild-core
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)
