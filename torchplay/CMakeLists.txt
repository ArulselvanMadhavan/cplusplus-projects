cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(torchplay VERSION 1.0.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(PYTORCH_VERSION "1.12.0")

find_package(Torch ${PYTORCH_VERSION} EXACT QUIET PATHS "${CMAKE_SOURCE_DIR}/libtorch")

if(NOT Torch_FOUND)
  unset(Torch_FOUND)
  include(fetch_libtorch)
endif()

set(EXECUTABLE_NAME torchplay)

add_executable(${EXECUTABLE_NAME})

target_sources(${EXECUTABLE_NAME} PRIVATE main.cpp)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  )

target_link_libraries(${EXECUTABLE_NAME} ${TORCH_LIBRARIES})

#add_subdirectory("extern")
#add_subdirectory("utils/image_io")

if(DOWNLOAD_DATASETS)
  set(DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data CACHE PATH "dataset download dir")
  file(MAKE_DIRECTORY ${DATA_DIR})
  add_custom_target(mnist COMMAND ${CMAKE_COMMAND}
    -D DATA_DIR=${DATA_DIR}
    -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/fetch_mnist.cmake)
endif()


add_subdirectory("tutorials/basics/pytorch_basics")
add_subdirectory("tutorials/basics/ffnn")
add_custom_target(basics)
add_dependencies(basics pytorch-basics)



