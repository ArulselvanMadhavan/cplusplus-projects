cmake_minimum_required(VERSION 3.21)

project(
  hello_world_standalone
  VERSION 1.0
  DESCRIPTION "Simple C++ project"
  HOMEPAGE_URL https://github.com/ArulselvanMadhavan
  LANGUAGES CXX
  )

add_executable(hello_world)
target_sources(hello_world PRIVATE src/main.cpp)
