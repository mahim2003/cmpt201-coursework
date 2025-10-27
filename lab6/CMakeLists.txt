cmake_minimum_required(VERSION 3.15)
project(cmpt201_lab6 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-g -O0 -Wall -Wextra -Wpedantic)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(example1 example_1.c)
add_executable(example2 example_2.c)
