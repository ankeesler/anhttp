include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("$ENV{ANHTTP_UNITY_ROOT}/src")

add_executable(server_test
    server_test.c
    "${PROJECT_SOURCE_DIR}/source/error.c"
    "${PROJECT_SOURCE_DIR}/source/server.c"
    "${PROJECT_SOURCE_DIR}/source/log.c"
    "${PROJECT_SOURCE_DIR}/source/syscall_stubs.c"
    "${PROJECT_SOURCE_DIR}/source/listener_stubs.c")
target_link_libraries(server_test unity)

add_executable(list_test list_test.c "${PROJECT_SOURCE_DIR}/source/list.c")
target_link_libraries(list_test unity)

add_executable(connection_queue_test
    connection_queue_test.c
    "${PROJECT_SOURCE_DIR}/source/connection_queue.c"
    "${PROJECT_SOURCE_DIR}/source/thread.c"
    "${PROJECT_SOURCE_DIR}/source/list.c"
    "${PROJECT_SOURCE_DIR}/source/error.c")
target_link_libraries(connection_queue_test unity)

add_executable(util_test
    util_test.c
    "${PROJECT_SOURCE_DIR}/source/util.c"
    "${PROJECT_SOURCE_DIR}/source/error.c")
target_link_libraries(util_test unity)

add_executable(listener_test
    listener_test.c
    "${PROJECT_SOURCE_DIR}/source/listener.c"
    "${PROJECT_SOURCE_DIR}/source/util.c"
    "${PROJECT_SOURCE_DIR}/source/log.c"
    "${PROJECT_SOURCE_DIR}/source/error.c"
    "${PROJECT_SOURCE_DIR}/source/thread_stubs.c"
    "${PROJECT_SOURCE_DIR}/source/connection_queue.c"
    "${PROJECT_SOURCE_DIR}/source/syscall_stubs.c")
target_link_libraries(listener_test unity)
