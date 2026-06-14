# CMake Target Helpers

This project uses small helper functions to avoid repeating CMake boilerplate across many binaries and libraries.

Files:

- `cmake/project_options.cmake`: reusable `project::options` and
  `project::warnings` interface targets.
- `cmake/project_targets.cmake`: helpers for libraries, app libraries, and executables.
- `cmake/project_tests.cmake`: helpers for unit, integration, and shell/e2e tests.

## Internal library

```cmake
project_add_library(protocol)

target_sources(protocol
    PRIVATE
        src/text_format.cpp
)

target_link_libraries(protocol
    PUBLIC
        project::common
)
```

## Header-only internal library

```cmake
project_add_interface_library(common)
```

## Binary application

Each binary should be split into an app library and a real executable:

```cmake
project_add_app_library(gateway_service_app)

target_sources(gateway_service_app
    PRIVATE
        bootstrap/bootstrap.cpp
)

project_add_executable(gateway_service)

target_sources(gateway_service
    PRIVATE
        main.cpp
)

target_link_libraries(gateway_service
    PRIVATE
        gateway_service_app
)
```

## Unit test

Tests use GoogleTest. The helper links `GTest::gtest_main` and registers each
GoogleTest case with CTest:

```cmake
project_add_test_executable(gateway_service_channel_domain_test)

target_sources(gateway_service_channel_domain_test
    PRIVATE
        tests/unit/channel_domain_test.cpp
)

target_link_libraries(gateway_service_channel_domain_test
    PRIVATE
        gateway_service_app
)
```

Test sources use the GoogleTest API and do not define `main()`:

```cpp
#include <gtest/gtest.h>

TEST(WirelessChannelTest, StoresValidChannel) {
    const WirelessChannel channel(15);

    EXPECT_EQ(channel.value(), 15);
}
```

## Rule

Use helpers for repeated mechanics:

- C++ standard
- warnings
- target aliases
- include directories
- test registration

Keep explicit per target:

- source files
- dependencies
- target name
- target type
