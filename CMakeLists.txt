cmake_minimum_required(VERSION 3.17)
project(assignment-6)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -pedantic)

set(
    SOURCES
    twoHashTable.cpp
    UPCEntry.cpp
)

add_subdirectory(tests)

add_executable(assignment-6 main.cpp ${SOURCES})
add_library(libassignment-6 STATIC ${SOURCES})