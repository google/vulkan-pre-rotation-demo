cmake_minimum_required(VERSION 3.4.1)

# glm
add_library(glm INTERFACE)
target_sources(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm/glm/glm.hpp)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm)
target_compile_definitions(glm INTERFACE GLM_FORCE_SIZE_T_LENGTH GLM_FORCE_RADIANS)

# stb
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/stb")
