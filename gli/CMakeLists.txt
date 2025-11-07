cmake_minimum_required(VERSION 3.28)

set(NAME gli)

file(GLOB ROOT_SOURCE *.cppm)
file(GLOB ROOT_SOURCE_IMPL *.cpp)
file(GLOB ROOT_TEXT ../*.txt)
file(GLOB ROOT_MD ../*.md)
file(GLOB ROOT_KMG ../doc/spec/*.html)

file(GLOB_RECURSE CORE_SOURCE ./core/*.cppm)

source_group("KMG Spec" FILES  ${ROOT_KMG})
source_group("Text Files" FILES ${ROOT_TEXT} ${ROOT_MD})
source_group("Core Files" FILES ${CORE_SOURCE})

add_library(${NAME} STATIC)

target_include_directories(${NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(${NAME} PRIVATE "glm_module")

set_target_properties(${NAME} PROPERTIES
  CXX_STANDARD 23
  POSITION_INDEPENDENT_CODE ON
)

target_sources(${NAME}
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    ${ROOT_SOURCE}
)

target_sources(${NAME}
  PRIVATE
    ${CORE_SOURCE}
    ${ROOT_SOURCE_IMPL}
)
