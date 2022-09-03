cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(recipe9 LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(animals
  SHARED
  Animal.cpp
  Animal.hpp
  Cat.cpp
  Cat.hpp
  Dog.cpp
  Dog.hpp
  Factory.hpp
  )

add_executable(animal-farm animal-farm.cpp)

set_target_properties(animal-farm
  PROPERTIES
  CXX_STANDARD 14
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON
  )

target_link_libraries(animal-farm animals)
