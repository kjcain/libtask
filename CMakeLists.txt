cmake_minimum_required(VERSION 3.16)

project(
    libtask
    VERSION 0.1
    LANGUAGES C
    DESCRIPTION "thread pools, asyncs, tasks, and lazy functions"
)

add_compile_options(
    -Wall
    -Wextra 
    -Werror 
    -Wformat-nonliteral
    -pedantic
    -O3
)

set(CMAKE_C_STANDARD 99)

# BEGIN BUILD LIBTASK
message("Loading headers")
include_directories(hdrs)

message("Loading source files")
file(GLOB LIBTASK_SOURCE_FILES src/*.c)

message("Building shared library")
add_library(task SHARED ${LIBTASK_SOURCE_FILES})

message("Linking libraries")
target_link_libraries(task pthread)
# END BUILD LIBTASK

# BEGIN BUILD TESTS
# expectations
# each test will be in the tests/ dir
# each test will be named name_in_list.c

list(APPEND MY_TESTS 
    test_threadpool
)

foreach(TARGET_TEST ${MY_TESTS})
    message("Adding Test tests/${TARGET_TEST}.c")
    add_executable(${TARGET_TEST} tests/${TARGET_TEST}.c)
    target_link_libraries(${TARGET_TEST} task)
    add_test(${TARGET_TEST} ${TARGET_TEST})
endforeach()

message("Enabling testing")
enable_testing()

# END BUILD TESTS