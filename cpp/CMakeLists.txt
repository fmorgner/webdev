cmake_minimum_required(VERSION 3.0)
project(shout CXX C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "The configuration to build" FORCE)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wno-unsupported-friend -Werror -pedantic -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(GnuTLS REQUIRED)

option(BUILD_UNIT_TESTS "Build the frontg8d unit tests" ON)

include_directories("include" "lib/redox/include")

add_subdirectory(lib)
add_subdirectory(src)

if(${BUILD_UNIT_TESTS})
  include(CUTE)
  add_subdirectory(test)
endif()

