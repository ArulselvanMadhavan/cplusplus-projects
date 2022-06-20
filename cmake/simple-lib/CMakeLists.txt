cmake_minimum_required(VERSION 3.21)
project(
  hello_lib
  VERSION 1.0
  DESCRIPTION "C++ lib"
  LANGUAGES CXX
)

add_library(hello)
target_sources(
  hello
  PRIVATE src/hello.cpp src/internal.cpp)

target_compile_features(hello PUBLIC cxx_std_17)
target_include_directories(
  hello
  PRIVATE src/hello
  PUBLIC include)
