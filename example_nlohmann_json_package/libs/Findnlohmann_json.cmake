# to avoid multiple library adding
if(TARGET nlohmann_json)
  return()
endif()

# ------------------------------------------------------------------------------------------
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set(nlohmann_json_DIR ${LIBS_DIR}/nlohmann_json)
set(nlohmann_json_INCLUDE_DIR ${nlohmann_json_DIR}/include)

# -----------------------------    Add nlohmann_json library    ----------------------------
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_INCLUDE_DIR})

# ------------------------------------------------------------------------------------------
# message("nlohmann_json_INCLUDE_DIR: ${nlohmann_json_INCLUDE_DIR}")
