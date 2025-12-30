cmake_minimum_required(VERSION 3.10)

project(ncfw)

find_package(Curses REQUIRED)

add_library(ncfw 
	src/nterm.cpp
	src/nwin.cpp
	src/ncont.cpp
)

target_link_libraries(ncfw PRIVATE ${CURSES_LIBRARIES})
target_include_directories(ncfw PRIVATE ${CURSES_INCLUDE_DIRS})

target_include_directories(ncfw PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

add_subdirectory(tests)
