file(GLOB SOURCES *.c)
add_library(mtest ${SOURCES})
target_include_directories(mtest PUBLIC .)