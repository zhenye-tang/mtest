cmake_minimum_required(VERSION 3.10)

project(mtest)

set (CMAKE_C_COMPILER "/usr/bin/gcc")
set (CMAKE_CXX_COMPILER "/usr/bin/g++")


add_executable(mtest main.c mtest.c)

target_compile_options(mtest PRIVATE -T/home/null/mtest/0.ld)

