
# eCAP library for HTTP Message Signatures (RFC 9421)

## REQMOD adaptation service

This library provides a REQMOD service
 `ecap://ecap-http-signatures/0.0.1/verify/request` which
 validates the Signature: header in HTTP Request messages.

This service is enabled by default in the provided
Squid configuration file `ecap-http-signatures.conf`.


# Compile and Build

## Requirements

 * cmake toolchain
 * A C++17 compiler
 * libecap version 1.0.0 or later

## Bootstrap with cmake

 `cmake -DCMAKE_INSTALL_PREFIX:PATH=/ .`

## Build and Install with make

 `make install`

