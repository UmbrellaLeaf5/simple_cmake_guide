cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME nice_hw)
project(${PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

set(TARGET_NAME ${PROJECT_NAME})

add_executable(
  ${TARGET_NAME}
  main.cpp
  hw.cpp
  hw.hpp
)