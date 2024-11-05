# language: CMake

# ---------------------------------     Project setup      ---------------------------------
cmake_minimum_required(VERSION 3.20)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

# ---------------------------------    Set C++ settings    ---------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++23 -O2")

# less speed, more warnings = less potential errors in code
# flags using source: https://codeforces.com/blog/entry/15547?locale=ru
# set(CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -std=c++23 -O2 -Wfloat-equal -Wconversion -Wlogical-op -Wduplicated-cond")

# ---------------------------------    Add subdirectories   --------------------------------
file(GLOB_RECURSE SUBDIRS LIST_DIRECTORIES true ".")

foreach(DIR ${SUBDIRS})
  IF(IS_DIRECTORY ${DIR})
    # message(${DIR})
    add_subdirectory(${DIR})
  ENDIF()
endforeach()