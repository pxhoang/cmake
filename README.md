# Sample Clean C++ Project

This is a small runnable C++ project that demonstrates:

- `bin/` for executable applications.
- `lib/` for internal libraries you own.
- `external/` for dependency metadata only.
- `.img/` for generated/downloaded/build/runtime/package output.
- Feature-oriented Clean Architecture inside a binary.
- Function-call API, not TCP/HTTP/router.
- Unit, integration, and e2e tests.
- GoogleTest-based C++ tests integrated with CTest.
- Docker-based build environment.
- Reusable CMake helper functions for many binaries and libraries.

## Build locally

```bash
./scripts/build.sh
```

## Test locally

```bash
./scripts/test.sh
```

## Run locally

```bash
./scripts/run.sh gateway_service
```

Expected output:

```text
radio_apply_channel: 15
Current channel: 15
```

## Build/test/run with Docker

```bash
./scripts/docker-test.sh
./scripts/docker-run.sh gateway_service
```

You only need Docker installed on your PC. The container provides CMake, Ninja, and G++.

The run scripts accept any application directory under `bin/`, so adding a binary
does not require adding more scripts:

```bash
./scripts/run.sh <binary> [args...]
./scripts/docker-run.sh <binary> [args...]
```

## CMake helper files

- `cmake/project_options.cmake`
- `cmake/project_targets.cmake`
- `cmake/project_tests.cmake`

See `docs/development/cmake.md`.

## Architecture flow

```text
main.cpp
    -> bootstrap
        -> ChannelApi
            -> use cases
                -> domain
                -> persistence
```

## Generated output policy

Generated files must go under `.img/`.

You can safely delete it:

```bash
./scripts/clean-img.sh
```
