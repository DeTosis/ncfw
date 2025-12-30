cmake_minimum_required(VERSION 3.10)

project(ncfw_tests)

find_package(Curses REQUIRED)

add_executable(ncfw_tests ncfw_tests.cpp)

target_link_libraries(ncfw_tests PRIVATE ${CURSES_LIBRARIES})
target_include_directories(ncfw_tests PRIVATE ${CURSES_INCLUDE_DIRS})

target_link_libraries(ncfw_tests PRIVATE ncfw)
