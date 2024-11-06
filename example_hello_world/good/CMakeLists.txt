cmake_minimum_required(VERSION 3.20)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++23 -O2")

file(GLOB SOURSE_FILES "*.cpp")
file(GLOB HEADER_FILES "*.hpp")

include_directories(${PROJECT_NAME})

add_executable(
  ${PROJECT_NAME}_hello_world
  ${SOURSE_FILES}
  ${HEADER_FILES}
)
