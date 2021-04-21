cmake_minimum_required(VERSION 3.6)
project(untitled1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL") # compiler version and compiler flags.
set(SOURCE_FILES main.cpp) # which files should be compiled
add_executable(untitled1 ${SOURCE_FILES}) # which files should produce executables