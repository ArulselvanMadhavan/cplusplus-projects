cmake_minimum_required(VERSION 3.21)

project(
  hello_static
  VERSION 1.0.0
  DESCRIPTION "Simple static hello world lib"
  LANGUAGES CXX
  )

add_library(hello_static STATIC)

# Output name will libhello.a
set_target_properties(
  hello_static
  PROPERTIES OUTPUT_NAME hello
  )

set_target_properties(
  hello_static
  PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}
  )

target_sources(hello_static PRIVATE src/hello.cpp src/internal.cpp)

target_compile_features(
  hello_static
  PUBLIC cxx_std_17
  )

target_include_directories(
  hello_static
  PRIVATE src/hello_static
  PUBLIC include
  )


