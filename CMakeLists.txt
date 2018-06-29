cmake_minimum_required (VERSION 3.11)
project (anhttp)

set(CMAKE_C_FLAGS "-g -ggdb -O0 -Wall -Werror")

include(CTest)
enable_testing()

add_subdirectory(source)
add_subdirectory(test)
