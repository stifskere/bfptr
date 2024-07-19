cmake_minimum_required(VERSION 3.28)
project(bfptr C)

set(CMAKE_C_STANDARD 11)

enable_testing()

add_library(bfptr STATIC src/bfptr.c)
target_include_directories(bfptr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(bfptr_tests tests/bfptr_test.c)
target_link_libraries(bfptr_tests PRIVATE bfptr)

add_test(NAME bfptr_tests COMMAND bfptr_tests)