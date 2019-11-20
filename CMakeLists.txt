cmake_minimum_required(VERSION 3.15)
project(library_system)

set(CMAKE_CXX_STANDARD 14)

add_executable(library_system main.cpp cmake-build-debug/ src/Student.cpp src/Student.h src/Book.cpp src/Book.h src/Root.cpp src/Root.h)