cmake_minimum_required(VERSION 2.8)

project(cpp-illustrated)

# Put our targets in top-level directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add C++17 support and warnings
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -pedantic-errors")

# Display compiler information
message(STATUS "CMAKE_CXX_COMPILER      : " ${CMAKE_CXX_COMPILER} )
message(STATUS "CMAKE_CXX_FLAGS         : " ${CMAKE_CXX_FLAGS} )
message(STATUS "CMAKE_BUILD_TYPE        : " ${CMAKE_BUILD_TYPE})

# Set build-specific configuration
if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-elide-constructors")
	set(BUILD_POSTFIX "_d")
#	add_definitions(-DLUANICS_LEAK_CHECKING)
	add_definitions(-DLUANICS_PROFILING)
	add_definitions(-DLUANICS_LOGGING)
	message(STATUS "CMAKE_CXX_FLAGS_DEBUG   : " ${CMAKE_CXX_FLAGS_DEBUG} )
elseif(CMAKE_BUILD_TYPE STREQUAL Profile)
	set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -DNDEBUG")
	add_definitions(-DLUANICS_PROFILING)
	set(BUILD_POSTFIX "_p")
	message(STATUS "CMAKE_CXX_FLAGS_PROFILE : " ${CMAKE_CXX_FLAGS_PROFILE} )
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
	set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -DNDEBUG")
	set(BUILD_POSTFIX "_r")
	message(STATUS "CMAKE_CXX_FLAGS_RELEASE : " ${CMAKE_CXX_FLAGS_RELEASE} )
else(CMAKE_BUILD_TYPE STREQUAL Debug)
	message(FATAL_ERROR "Unhandled CMAKE_BUILD_TYPE : " $CMAKE_BUILD_TYPE)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

include_directories(.)

add_subdirectory(book)
add_subdirectory(luanics)
add_subdirectory(tutorial)
