include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(echo_example echo/main.c)
target_link_libraries(echo_example anhttp)
