cmake_minimum_required(VERSION 2.8.7)
project(mininet C CXX)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CLANG_COMPILER TRUE)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(GCC_COMPILER TRUE)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(MSVC_COMPILER TRUE)
endif()

# Build options.
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCUMENTATION "Build documentation" OFF)
if(GCC_COMPILER)
    set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
endif()

# Extra variables.
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  add_definitions(-DSYSTEM_OSX)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  add_definitions(-DSYSTEM_LINUX)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

add_definitions(-DMININET_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")

# Add cmake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
message("Cmake module path: ${CMAKE_MODULE_PATH}")

# Add cmake utilities.
include(cmake/Utils.cmake)

# Add dependencies.
include(cmake/Dependencies.cmake)

# Check for C++11 features and enable.
mininet_enable_cpp11()

# Set the build type. Default to Release mode.
if(NOT CMAKE_BUILD_TYPE)
  message("Defaulting to building targets in Release mode.")
  set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

# Find and build third party libraries.
add_subdirectory(external)

# Add the source directories to the search path so cmake can find our headers.
set(CMAKE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_INCLUDE_DIR})

# Collect source files and build the berkeley_sfm object.
file(GLOB_RECURSE mininet_srcs ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(mininet ${mininet_srcs})

# Set up output directory for executables.
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)

# Find and build executables.
add_subdirectory(exec)

# Find and build tests.
if (BUILD_TESTS)
  message("Build tests is enabled.")
  add_subdirectory(test)
endif (BUILD_TESTS)

# Installation.
install(TARGETS mininet DESTINATION /usr/local/lib)
install(DIRECTORY ${CMAKE_INCLUDE_DIR}/ DESTINATION /usr/local/include/mininet)

# Find and build documentation.
#if (BUILD_DOCUMENTATION)
#  message("Build documentation is enabled.")
#  add_subdirectory(documentation)
#endif (BUILD_DOCUMENTATION)
