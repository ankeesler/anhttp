cmake_minimum_required (VERSION 3.11)
project (anhttp)

if (DEFINED ENV{ANHTTP_UNITY_ROOT})
    message(STATUS "ANHTTP_UNITY_ROOT is set to $ENV{ANHTTP_UNITY_ROOT}")
else()
    message(FATAL_ERROR "ANHTTP_UNITY_ROOT is not set")
endif()

set(CMAKE_C_FLAGS "-g -ggdb -O0 -Wall -Werror")

add_subdirectory(third_party)
add_subdirectory(source)
add_subdirectory(test)
add_subdirectory(examples)
