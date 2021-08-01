cmake_minimum_required(VERSION 3.10)
project(assignment2)

set(CMAKE_CXX_STANDARD 11)

include_directories(./)

file(COPY tests/words.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY madlibs1.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(user_test tests/user_test.cpp MadLibsController.cpp MadlibUserWordProvider.cpp MadlibAutoWordProvider.cpp)
add_executable(auto_test tests/auto_test.cpp MadLibsController.cpp MadlibUserWordProvider.cpp MadlibAutoWordProvider.cpp)
add_executable(auto_test_plural tests/auto_test_plural.cpp MadLibsController.cpp MadlibUserWordProvider.cpp MadlibAutoWordProvider.cpp)
add_executable(controller_test tests/controller_test.cpp MadLibsController.cpp MadlibUserWordProvider.cpp MadlibAutoWordProvider.cpp)
add_executable(line_level_token_match tests/line_level_token_match.cpp MadLibsController.cpp MadlibUserWordProvider.cpp MadlibAutoWordProvider.cpp)

add_executable(main main.cpp MadLibsController.cpp MadlibUserWordProvider.cpp MadlibAutoWordProvider.cpp)