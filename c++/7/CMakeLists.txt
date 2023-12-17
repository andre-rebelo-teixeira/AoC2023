cmake_minimum_required(VERSION 3.27)

set(current_executable_name 7)
project(AOC2023_${current_executable_name})

message(${PROJECT_NAME})

# C - 11 as standart
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

# C ++ 23 as standar
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -g)
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
