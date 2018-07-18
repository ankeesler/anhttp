cc_test(
    name = "list_test",
    srcs = ["list_test.c"],
    copts = ["-Iexternal/unity/src", "-Iinclude", "-I."],
    deps = [
        "@unity//:unity",
        "//source:list_lib",
    ],
)

cc_test(
    name = "util_test",
    srcs = ["util_test.c"],
    copts = ["-Iexternal/unity/src", "-Iinclude", "-I."],
    deps = [
        "@unity//:unity",
        "//source:util_lib",
        "//source:core_lib",
        "//include/anhttp:anhttp",
    ],
)

cc_test(
    name = "connection_queue_test",
    srcs = ["connection_queue_test.c"],
    copts = ["-Iexternal/unity/src", "-Iinclude", "-I."],
    deps = [
        "@unity//:unity",
        "//source:connection_queue_lib",
        "//source:core_lib",
        "//source:thread_lib",
        "//source:list_lib",
        "//include/anhttp:anhttp",
    ],
)

cc_test(
    name = "listener_test",
    srcs = ["listener_test.c"],
    copts = ["-Iexternal/unity/src", "-Iinclude", "-I."],
    deps = [
        "@unity//:unity",
        "//source:listener_lib",
        "//source:core_lib",
        "//source:list_lib",
        "//source:util_lib",
        "//source:syscall_stubs_lib",
        "//source:thread_stubs_lib",
        "//source:connection_queue_stubs_lib",
        "//include/anhttp:anhttp",
    ],
)

cc_test(
    name = "server_test",
    srcs = ["server_test.c"],
    copts = ["-Iexternal/unity/src", "-Iinclude", "-I."],
    deps = [
        "@unity//:unity",
        "//source:core_lib",
        "//source:server_lib",
        "//source:thread_stubs_lib",
        "//source:syscall_stubs_lib",
        "//source:connection_queue_stubs_lib",
        "//source:listener_stubs_lib",
        "//source:util_lib",
        "//source:http_stubs_lib",
        "//include/anhttp:anhttp",
    ],
)
