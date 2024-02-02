project(example)

file(GLOB SOURCES *.c)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -O0 -Wl,-Map=Mtest.map")

message(STATUS ${CUSTOM_LINKER_SCRIPT_PATH})
# Generate executable
add_executable(example
        ${SOURCES}
)
target_link_libraries(example mtest)
target_link_options(example PRIVATE "-T${CUSTOM_LINKER_SCRIPT_PATH}")



