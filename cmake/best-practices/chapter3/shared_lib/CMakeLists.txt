cmake_minimum_required(VERSION 3.21)

project(
  hello_shared
  VERSION 1.0.0
  DESCRIPTION "C++-shared lib"
  LANGUAGES CXX
)

set(CMAKE_DEBUG_POSTFIX d)

add_library(hello_shared SHARED)

set_target_properties(
  hello_shared
  PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_sources(
  hello_shared
  PRIVATE src/hello.cpp src/internal.cpp
)

target_compile_features(
  hello_shared
  PUBLIC cxx_std_17
  )

target_include_directories(
  hello_shared
  PRIVATE src/hello_shared
  PUBLIC include
  )

include(GenerateExportHeader)
set_property(
  TARGET hello_shared
  PROPERTY CXX_VISIBILITY_PRESET "hidden"
  )
set_property(
  TARGET hello_shared
  PROPERTY VISIBILITY_INLINES_HIDDEN TRUE
  )

generate_export_header(
  hello_shared
  EXPORT_FILE_NAME
  export/hello/export_hello.hpp
  )

target_include_directories(
  hello_shared
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/export"
  )


