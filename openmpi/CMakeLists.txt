cmake_minimum_required(VERSION 2.8)

project(mpiplayground)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(MPI REQUIRED)

add_library(timer timer.c)
add_library(malloc2D malloc2D.c)

function (add_new exec_name file)
  add_executable(${exec_name} ${file})
  target_include_directories(${exec_name}
    PRIVATE ${MPI_C_INCLUDE_PATH})
  target_compile_options(${exec_name}
    PRIVATE ${MPI_C_COMPILE_FLAGS})
  target_link_libraries(${exec_name}
    ${MPI_C_LIBRARIES} ${MPI_C_LINK_FLAGS} "m" timer malloc2D)
  # target_link_libraries(${exec_name} PRIVATE "m")
endfunction()

add_new(MinWorkExample MinWorkExample.c)
add_new(SendRecv SendRecv.c)
add_new(GlobalSums globalsums.c)
add_new(FileRead FileRead.c)
add_new(SynchronizedTimer SynchronizedTimer.c)
add_new(GhostExchange GhostExchange.cc)

enable_testing()

# add_test(MPITest ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG}
#   ${MPIEXEC_MAX_NUMPROCS}
#   ${MPIEXEC_PREFLAGS}
#   ${CMAKE_CURRENT_BINARY_DIR}/SendRecv
#   ${MPIEXEC_POSTFLAGS}
# )

add_custom_target(distclean
  COMMAND rm -rf CMakeCache.txt CMakeFiles Makefile cmake_install.cmake CTestTestfile.cmake Testing)

add_custom_command(
  TARGET FileRead PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_SOURCE_DIR}/file.in
  ${CMAKE_CURRENT_BINARY_DIR}/file.in
  )

add_custom_command(
        TARGET FileRead POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
	${CMAKE_SOURCE_DIR}/compile_commands.json
	DEPENDS CMakeLists.txt)
