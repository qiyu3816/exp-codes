cmake_minimum_required(VERSION 3.1)
if(EXISTS /usr/bin/clang AND EXISTS /usr/bin/clang++)
   set(CMAKE_C_COMPILER /usr/bin/clang)
   set(CMAKE_CXX_COMPILER /usr/bin/clang++)
endif()
project(ojs)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(TEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ex2)

macro(add_test_file TEST_FILE)
    add_executable(${TEST_FILE} ${TEST_PATH}/${TEST_FILE}.cpp)
endmacro()

add_test_file(SampleGenerate)
add_test_file(DFS)
add_test_file(BFS)
