cmake_minimum_required(VERSION 3.21)

project(
  simple_lib
  VERSION 1.0
  DESCRIPTION "Lib example"
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(static_lib)
add_subdirectory(shared_lib)
add_subdirectory(header_only)
add_subdirectory(object_lib)

add_executable(simplelib)
target_sources(simplelib PRIVATE src/main.cpp)
target_link_libraries(simplelib PRIVATE hello_shared hello_header hello_object)


