cmake_minimum_required(VERSION 3.0)
project(shout CXX C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "The configuration to build" FORCE)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wno-unsupported-friend -Werror -pedantic -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/products/${CMAKE_BUILD_TYPE}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/products/${CMAKE_BUILD_TYPE}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/products/${CMAKE_BUILD_TYPE}/lib")

find_package(GnuTLS REQUIRED)

option(BUILD_UNIT_TESTS "Build the frontg8d unit tests" ON)

add_subdirectory(lib)

include_directories("include" "lib/redox/include" ${mstch_INCLUDE_DIR})

add_subdirectory(src)

if(${BUILD_UNIT_TESTS})
  include(CUTE)
  add_subdirectory(test)
endif()

