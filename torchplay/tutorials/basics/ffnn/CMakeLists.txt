cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(ffnn VERSION 1.0.0 LANGUAGES CXX)

set(EXECUTABLE_NAME ffnn)

add_executable(${EXECUTABLE_NAME})

target_sources(${EXECUTABLE_NAME}
  PRIVATE
  src/main.cpp
  src/neural_net.cpp
  include/neural_net.h
  )

target_include_directories(${EXECUTABLE_NAME} PRIVATE include)

target_link_libraries(${EXECUTABLE_NAME} ${TORCH_LIBRARIES})

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  )

if(DOWNLOAD_DATASETS)
  add_dependencies(${EXECUTABLE_NAME} mnist)
endif()

