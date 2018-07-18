cc_library(
    name = "core_lib",
    srcs = [
        "error.c",
        "log.c",
    ],
    hdrs = ["log.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = ["//include/anhttp"],
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
    visibility = ["//visibility:public"],
    deps = ["//include/anhttp"],
)

cc_library(
    name = "syscall_stubs_lib",
    srcs = [
        "syscall.h",
        "syscall_stubs.c",
    ],
    hdrs = ["syscall_stubs.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = ["//include/anhttp"],
)

cc_library(
    name = "util_lib",
    srcs = ["util.c"],
    hdrs = ["util.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = ["//include/anhttp"],
)

cc_library(
    name = "thread_lib",
    srcs = ["thread.c"],
    hdrs = ["thread.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = ["//include/anhttp"],
)

cc_library(
    name = "thread_stubs_lib",
    srcs = [
        "thread.h",
        "thread_stubs.c",
    ],
    hdrs = ["thread_stubs.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = ["//include/anhttp"],
)

cc_library(
    name = "connection_queue_lib",
    srcs = ["connection_queue.c"],
    hdrs = ["connection_queue.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = ["//include/anhttp"],
)

cc_library(
    name = "connection_queue_stubs_lib",
    srcs = [
        "connection_queue.h",
        "connection_queue_stubs.c",
    ],
    hdrs = ["connection_queue_stubs.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = ["//include/anhttp"],
)

cc_library(
    name = "listener_lib",
    srcs = [
        "connection_queue.h",
        "listener.c",
        "log.h",
        "syscall.h",
        "thread.h",
        "util.h",
    ],
    hdrs = ["listener.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = [
        "//include/anhttp",
    ],
)

cc_library(
    name = "listener_stubs_lib",
    srcs = [
        "connection_queue.h",
        "listener.h",
        "listener_stubs.c",
        "syscall.h",
        "thread.h",
    ],
    hdrs = ["listener_stubs.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = [
        "//include/anhttp",
    ],
)

cc_library(
    name = "http_lib",
    srcs = ["http.c"],
    hdrs = ["http.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = [
        ":core_lib",
        "//include/anhttp",
    ],
)

cc_library(
    name = "http_stubs_lib",
    srcs = [
        "http.h",
        "http_stubs.c",
    ],
    hdrs = ["http_stubs.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = [
        "//include/anhttp",
    ],
)

cc_library(
    name = "server_lib",
    srcs = [
        "connection_queue.h",
        "http.h",
        "log.h",
        "server.c",
        "syscall.h",
        "thread.h",
    ],
    hdrs = ["listener.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = [
        "//include/anhttp",
    ],
)

cc_library(
    name = "anhttp",
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"],
    deps = [
        ":connection_queue_lib",
        ":core_lib",
        ":http_lib",
        ":listener_lib",
        ":server_lib",
        ":syscall_lib",
        ":thread_lib",
        ":util_lib",
        "//include/anhttp",
    ],
)
