cc_test(
    name = "list_test",
    srcs = ["list_test.c"],
    copts = [
        "-Iexternal/unity/src",
        "-Iinclude",
        "-I.",
        "-Wall",
        "-Werror",
    ],
    deps = [
        "//source:list_lib",
        "@unity",
    ],
)

cc_test(
    name = "util_test",
    srcs = ["util_test.c"],
    copts = [
        "-Iexternal/unity/src",
        "-Iinclude",
        "-I.",
        "-Wall",
        "-Werror",
    ],
    deps = [
        "//include/anhttp",
        "//source:core_lib",
        "//source:util_lib",
        "@unity",
    ],
)

cc_test(
    name = "connection_queue_test",
    srcs = ["connection_queue_test.c"],
    copts = [
        "-Iexternal/unity/src",
        "-Iinclude",
        "-I.",
        "-Wall",
        "-Werror",
    ],
    deps = [
        "//include/anhttp",
        "//source:connection_queue_lib",
        "//source:core_lib",
        "//source:list_lib",
        "//source:thread_lib",
        "@unity",
    ],
)

cc_test(
    name = "listener_test",
    srcs = ["listener_test.c"],
    copts = [
        "-Iexternal/unity/src",
        "-Iinclude",
        "-I.",
        "-Wall",
        "-Werror",
    ],
    deps = [
        "//include/anhttp",
        "//source:connection_queue_stubs_lib",
        "//source:core_lib",
        "//source:list_lib",
        "//source:listener_lib",
        "//source:syscall_stubs_lib",
        "//source:thread_stubs_lib",
        "//source:util_lib",
        "@unity",
    ],
)

cc_test(
    name = "server_test",
    srcs = ["server_test.c"],
    copts = [
        "-Iexternal/unity/src",
        "-Iinclude",
        "-I.",
        "-Wall",
        "-Werror",
    ],
    deps = [
        "//include/anhttp",
        "//source:connection_queue_stubs_lib",
        "//source:core_lib",
        "//source:http_stubs_lib",
        "//source:listener_stubs_lib",
        "//source:server_lib",
        "//source:syscall_stubs_lib",
        "//source:thread_stubs_lib",
        "//source:util_lib",
        "@unity",
    ],
)
