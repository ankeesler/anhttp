cmake_minimum_required (VERSION 3.11)
project (anhttp)

# TODO: assert that ANHTTP_UNITY_ROOT is defined.
# TODO: stop building this stuff in this directory!

set(CMAKE_C_FLAGS "-g -ggdb -O0 -Wall -Werror")

add_subdirectory(third_party)
add_subdirectory(source)
add_subdirectory(test)
