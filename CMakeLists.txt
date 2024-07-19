cmake_minimum_required(VERSION 3.28)
project(bfptr C)

set(CMAKE_C_STANDARD 11)

enable_testing()

add_library(bfptr STATIC src/bfptr.c include/bfptr.h)
target_include_directories(bfptr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

function(add_bfptr_test test_description test_name source_file)
    add_executable(${test_name} ${source_file})
    target_link_libraries(${test_name} PRIVATE bfptr)
    add_test(NAME ${test_description} COMMAND ${test_name})
endfunction()

add_bfptr_test("byte limits" bfptr_test_limits tests/limits.c)
add_bfptr_test("go left until last again" bfptr_test_left_until_last tests/left_until_last.c)
add_bfptr_test("go right until first again" bfptr_test_right_until_first tests/right_until_first.c)
add_bfptr_test("store hello world" bfptr_hello_world tests/hello_world.c)