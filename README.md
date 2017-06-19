# Envoy filter example

This project adds linking of additional filters with the Envoy binary.
A new filter `s4n` is introduced, based on [`echo`](https://github.com/lyft/envoy/blob/master/source/common/filter/echo.h)
filter. Integration tests demonstrating the filter's end-to-end behavior are
also provided.

## Building

To build the Envoy static binary:

1. `git submodule update --init`
2. `bazel build //:envoy`

## Testing

To run the `s4n` integration test:

`bazel test //:s4n_integration_test`

To run the regular Envoy tests from this project:

`bazel test @envoy//...`

## How it works

The [Envoy repository](https://github.com/lyft/envoy/) is provided as a submodule.
The [`WORKSPACE`](WORKSPACE) file maps the `@envoy` repository to this local path.

The [`BUILD`](BUILD) file introduces a new Envoy static binary target, `envoy`,
that links together the new filter and `@envoy//source/exe:envoy_main_lib`. The
`s4n` filter registers itself during the static initialization phase of the
Envoy binary as a new filter.
