include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(anhttp
    syscall.c thread.c
    error.c list.c log.c util.c connection_queue.c
    listener.c
    server.c)
