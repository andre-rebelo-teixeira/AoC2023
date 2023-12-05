cmake_minimum_required(VERSION 3.27)

project(AOC2023_4)

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

set(executable_1_name ${PROJECT_NAME}_1)

set(executable_2_name ${PROJECT_NAME}_2)

add_executable(${executable_1_name} 
  first.cpp
)

add_executable(${executable_2_name}
  second.cpp
)
