cmake_minimum_required(VERSION 2.8)

project(MinWorkExample)

find_package(MPI REQUIRED)

add_executable(MinWorkExample MinWorkExample.c)

target_include_directories(MinWorkExample
  PRIVATE ${MPI_C_INCLUDE_PATH})
target_compile_options(MinWorkExample
  PRIVATE ${MPI_C_COMPILE_FLAGS})
target_link_libraries(MinWorkExample
  ${MPI_C_LIBRARIES} ${MPI_C_LINK_FLAGS})

enable_testing()
add_test(MPITest ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG}
  ${MPIEXEC_MAX_NUMPROCS}
  ${MPIEXEC_PREFLAGS}
  ${CMAKE_CURRENT_BINARY_DIR}/MinWorkExample
  ${MPIEXEC_POSTFLAGS}
  )

add_custom_target(distclean
  COMMAND rm -rf CMakeCache.txt CMakeFiles Makefile cmake_install.cmake CTestTestfile.cmake Testing)
