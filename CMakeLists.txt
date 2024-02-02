cmake_minimum_required(VERSION 3.10)

project(Mtest)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wl,-Map=Mtest.map")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CUSTOM_LINKER_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/0.lds")

add_subdirectory(src)
add_executable(Mtest main.c examples/testcase_0.c)
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Mtest mtest)


target_link_options(Mtest PRIVATE "-T${CUSTOM_LINKER_SCRIPT_PATH}")