include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(anhttp_test main.c)
target_link_libraries(anhttp_test anhttp)
add_test(anhttp_test anhttp_test)
