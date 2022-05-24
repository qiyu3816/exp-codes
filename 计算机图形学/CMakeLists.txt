cmake_minimum_required(VERSION 3.1)
if(EXISTS /usr/bin/clang AND EXISTS /usr/bin/clang++)
   set(CMAKE_C_COMPILER /usr/bin/clang)
   set(CMAKE_CXX_COMPILER /usr/bin/clang++)
endif()

if (POLICY CMP0072)
  set(OpenGL_GL_PREFERENCE LEGACY)
endif()

project(ComputerGraphics)

set(CMAKE_CXX_STANTARD 11)
set(TEST_PATH ${CMAKE_CURRENT_LIST_DIR}/src)

# g++ -o test test.cpp -lGL -lGLU -lglut
macro(add_test_file TEST_FILE)
    add_executable(${TEST_FILE} ${TEST_PATH}/${TEST_FILE}.cpp)
    target_link_libraries(${TEST_FILE} GL GLU glut)
endmacro()

add_test_file(OpenGLTest)

add_test_file(DrawCubic)
add_test_file(DrawPolygon)
add_test_file(DrawCircle)
add_test_file(DrawLine)
add_test_file(DrawPoint)
