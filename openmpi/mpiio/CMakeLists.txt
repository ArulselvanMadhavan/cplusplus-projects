cmake_minimum_required(VERSION 3.0)
project(mpi_io_block2d LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
find_package(MPI REQUIRED)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})
# find_package(Vector)

add_executable(mpi_io_block2d mpi_io_block2d.c malloc2D.c)
set_target_properties(mpi_io_block2d PROPERTIES INCLUDE_DIRECTORIES "${MPI_C_INCLUDE_PATH}")
set_target_properties(mpi_io_block2d PROPERTIES COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")
set_target_properties(mpi_io_block2d PROPERTIES LINK_FLAGS "${MPI_C_LINK_FLAGS}")
target_link_libraries(mpi_io_block2d ${MPI_C_LIBRARIES})

# Cleanup
add_custom_target(distclean COMMAND rm -rf CMakeCache.txt CMakeFiles
                  Makefile cmake_install.cmake *.data)

add_custom_command(
        TARGET mpi_io_block2d POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
	${CMAKE_SOURCE_DIR}/compile_commands.json
	DEPENDS CMakeLists.txt)
