cmake_minimum_required(VERSION 3.20)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++23 -O2")

file(GLOB_RECURSE SOURCE_LIST "src/*.cpp" "src/*.hpp" "src/*.h")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/libs)
include_directories(${CMAKE_CURRENT_LIST_DIR}/libs)

string(REPLACE "example_" "" TARGET_NAME "${PROJECT_NAME}")

find_package(nlohmann_json REQUIRED)

add_executable(${TARGET_NAME} ${SOURCE_LIST})
target_link_libraries(${TARGET_NAME} nlohmann_json)

file(GLOB_RECURSE EXTRA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB_RECURSE PROJECT_FILES "*.cpp" "*.h" "*.hpp" "*.c" ".md")
list(REMOVE_ITEM EXTRA_FILES ${PROJECT_FILES})

file(COPY ${EXTRA_FILES} DESTINATION ${PROJECT_BINARY_DIR})
