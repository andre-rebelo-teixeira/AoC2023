cmake_minimum_required(VERSION 3.27)

project(AOC2023_1)

# C - 11 as standart
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

# C ++ 20 as standar
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aoc_2023_ex2_1 
  first.cpp
)

add_executable(aoc2023_ex2_2
  second.cpp
)
