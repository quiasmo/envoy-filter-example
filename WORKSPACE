workspace(name = "envoy")

local_repository(
    name = "envoy",
    path = "/source",
)

load("@envoy//bazel:repositories.bzl", "envoy_dependencies")
load("@envoy//bazel:cc_configure.bzl", "cc_configure")

envoy_dependencies()

cc_configure()
