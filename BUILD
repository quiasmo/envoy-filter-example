package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
)

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        ":s4n_config",
        "@envoy//source/exe:envoy_main_lib",
    ],
)

envoy_cc_library(
    name = "s4n_lib",
    srcs = ["s4n.cc"],
    hdrs = ["s4n.h"],
    external_deps = ["tinyxml2"],
    repository = "@envoy",
    deps = [
        "@envoy//include/envoy/buffer:buffer_interface",
        "@envoy//include/envoy/http:filter_interface",
        "@envoy//source/common/common:assert_lib",
        "@envoy//source/common/common:logger_lib",
        "@envoy//source/common/buffer:buffer_lib",
    ],
)

envoy_cc_library(
    name = "s4n_config",
    srcs = ["s4n_config.cc"],
    repository = "@envoy",
    deps = [
        ":s4n_lib",
        "@envoy//source/server:configuration_lib",
    ],
)

envoy_cc_test(
    name = "s4n_integration_test",
    srcs = ["s4n_integration_test.cc"],
    data =  ["s4n_server.json"],
    repository = "@envoy",
    deps = [
        ":s4n_config",
        "@envoy//test/integration:integration_lib",
    ],
)
