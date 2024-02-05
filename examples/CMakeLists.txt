project(example)

file(GLOB SOURCES *.c)

set(CUSTOM_LINKER_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/0.lds")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

message(STATUS ${CUSTOM_LINKER_SCRIPT_PATH})
# Generate executable
add_executable(example
        ${SOURCES}
)
target_link_libraries(example mtest)
target_link_options(example PRIVATE "-T${CUSTOM_LINKER_SCRIPT_PATH}")



