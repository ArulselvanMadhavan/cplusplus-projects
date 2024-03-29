cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(cnn VERSION 1.0.0 LANGUAGES CXX)

set(EXECUTABLE_NAME cnn)

add_executable(${EXECUTABLE_NAME})

target_sources(${EXECUTABLE_NAME} PRIVATE src/main.cpp
  src/convnet.cpp
  src/imagefolder_dataset.cpp
  include/convnet.h
  include/imagefolder_dataset.h)

target_include_directories(${EXECUTABLE_NAME} PRIVATE include)
target_link_libraries(${EXECUTABLE_NAME} ${TORCH_LIBRARIES} image-io)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  )

if(DOWNLOAD_DATASETS)
  add_dependencies(${EXECUTABLE_NAME} imagenette)
endif()

