project(tests)

add_subdirectory(googletest)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(tests twoHashTable.cpp UPCEntry.cpp)
target_link_libraries(tests gtest gtest_main libassignment-6)