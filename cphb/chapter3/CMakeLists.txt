cmake_minimum_required(VERSION 3.25)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  ch3_standalone
  VERSION 1.0
  DESCRIPTION "chapter 3 of Competitive Prog. Handbook"
  HOMEPAGE_URL https://github.com/ArulselvanMadhavan
  LANGUAGES CXX
)

add_executable(sample)
target_sources(sample PRIVATE sample.cpp)
target_compile_features(sample PUBLIC cxx_std_17)
add_executable(mm)
target_sources(mm PRIVATE mm.cpp)
set_target_properties(mm PROPERTIES CXX_STANDARD 17)
