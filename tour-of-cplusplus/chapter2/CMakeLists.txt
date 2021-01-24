cmake_minimum_required(VERSION 3.10)

project(Chapter2 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# option(USE_MYMATH "Use tutorial provided math implementation" ON)
# configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(Chapter2 union.cc)

# if(USE_MYMATH)
#   add_subdirectory(MathFunctions)
#   list(APPEND EXTRA_LIBS MathFunctions)
# endif()

# target_link_libraries(Chapter2 PUBLIC ${EXTRA_LIBS})
# target_include_directories(Chapter2 PUBLIC
#                            "${PROJECT_BINARY_DIR}"
#                            )

# install(TARGETS Chapter2 DESTINATION bin)
# install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION
# include)

# enable_testing()
# add_test(NAME Runs COMMAND Chapter2 25)
# add_test(NAME Usage COMMAND Chapter2)
# set_tests_properties(Usage
#   PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
#   )

# function(do_test target arg result)
#   add_test(NAME Comp${arg} COMMAND ${target} ${arg})
#   set_tests_properties(Comp${arg}
#     PROPERTIES PASS_REGULAR_EXPRESSION ${result}
#     )
# endfunction(do_test)

# do_test(Chapter2 4 "4 is 2")
# do_test(Chapter2 9 "9 is 3")
# do_test(Chapter2 5 "5 is 2.236")
# do_test(Chapter2 7 "7 is 2.645")
# do_test(Chapter2 25 "25 is 5")
# do_test(Chapter2 -25 "-25 is [-nan|nan|0]")
# do_test(Chapter2 0.0001 "0.0001 is 0.01")

