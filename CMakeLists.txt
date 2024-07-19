cmake_minimum_required(VERSION 3.28)
project(bfptr C)

set(CMAKE_C_STANDARD 11)

enable_testing()

add_library(bfptr STATIC src/bfptr.c)
target_include_directories(bfptr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(bfptr_test_limits tests/limits.c)
target_link_libraries(bfptr_test_limits PRIVATE bfptr)

add_executable(bfptr_test_left_until_last tests/left_until_last.c)
target_link_libraries(bfptr_test_left_until_last PRIVATE bfptr)

add_executable(bfptr_test_right_until_first tests/right_until_first.c)
target_link_libraries(bfptr_test_right_until_first PRIVATE bfptr)

add_executable(bfptr_test_hello_world tests/hello_world.c)
target_link_libraries(bfptr_test_hello_world PRIVATE bfptr)

add_test(NAME "byte limits" COMMAND bfptr_test_limits)
add_test(NAME "go left until last again" COMMAND bfptr_test_left_until_last)
add_test(NAME "go right until first again" COMMAND bfptr_test_right_until_first)
add_test(NAME "store hello world" COMMAND bfptr_test_hello_world)