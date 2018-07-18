cc_library(
    name = "anhttp",
    srcs = [
      "connection_queue.c",
      "connection_queue.h",
      "error.c",
      "http.c",
      "http.h",
      "list.c",
      "list.h",
      "listener.c",
      "listener.h",
      "log.c",
      "log.h",
      "server.c",
      "syscall.c",
      "syscall.h",
      "thread.c",
      "thread.h",
      "util.c",
      "util.h",
    ],
    copts = ["-Iinclude"],
    deps = ["//include/anhttp:anhttp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "core_lib",
    srcs = ["error.c", "log.c"],
    hdrs = ["log.h"],
    copts = ["-Iinclude"],
    deps = ["//include/anhttp:anhttp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "list_lib",
    srcs = ["list.c"],
    hdrs = ["list.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "syscall_lib",
    srcs = ["syscall.c"],
    hdrs = ["syscall.h"],
    copts = ["-Iinclude"],
    deps = ["//include/anhttp:anhttp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "syscall_stubs_lib",
    srcs = ["syscall_stubs.c", "syscall.h"],
    hdrs = ["syscall_stubs.h"],
    copts = ["-Iinclude"],
    deps = ["//include/anhttp:anhttp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "util_lib",
    srcs = ["util.c"],
    hdrs = ["util.h"],
    copts = ["-Iinclude"],
    deps = ["//include/anhttp:anhttp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "connection_queue_lib",
    srcs = ["connection_queue.c"],
    hdrs = ["connection_queue.h"],
    copts = ["-Iinclude"],
    deps = ["//include/anhttp:anhttp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "connection_queue_stubs_lib",
    srcs = ["connection_queue_stubs.c", "connection_queue.h"],
    hdrs = ["connection_queue_stubs.h"],
    copts = ["-Iinclude"],
    deps = ["//include/anhttp:anhttp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "thread_lib",
    srcs = ["thread.c"],
    hdrs = ["thread.h"],
    copts = ["-Iinclude"],
    deps = ["//include/anhttp:anhttp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "thread_stubs_lib",
    srcs = ["thread_stubs.c", "thread.h"],
    hdrs = ["thread_stubs.h"],
    copts = ["-Iinclude"],
    deps = ["//include/anhttp:anhttp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "listener_lib",
    srcs = ["listener.c", "thread.h", "connection_queue.h", "syscall.h", "log.h", "util.h"],
    hdrs = ["listener.h"],
    copts = ["-Iinclude"],
    deps = [
        "//include/anhttp:anhttp",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "listener_stubs_lib",
    srcs = ["listener_stubs.c", "listener.h"],
    hdrs = ["listener_stubs.h"],
    copts = ["-Iinclude"],
    deps = [
        ":thread_lib",
        ":connection_queue_lib",
        ":syscall_lib",
        "//include/anhttp:anhttp",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "http_lib",
    srcs = ["http.c"],
    hdrs = ["http.h"],
    copts = ["-Iinclude"],
    deps = [
        ":core_lib",
        "//include/anhttp:anhttp",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "http_stubs_lib",
    srcs = ["http_stubs.c", "http.h"],
    hdrs = ["http_stubs.h"],
    copts = ["-Iinclude"],
    deps = [
        "//include/anhttp:anhttp",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "server_lib",
    srcs = ["server.c", "thread.h", "connection_queue.h", "syscall.h", "log.h", "http.h"],
    hdrs = ["listener.h"],
    copts = ["-Iinclude"],
    deps = [
        #":thread_lib",
        #":connection_queue_lib",
        #":syscall_lib",
        #":core_lib",
        #":http_lib",
        "//include/anhttp:anhttp",
    ],
    visibility = ["//visibility:public"],
)
