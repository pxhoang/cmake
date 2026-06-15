# Architecture Overview

The project uses feature-oriented Clean Architecture inside each binary.
Architectural layers are separate CMake targets, so forbidden dependencies fail
at compile time instead of relying only on directory conventions.

Gateway target graph:

```mermaid
graph TD
    Service["gateway_service"] --> Composition["gateway_composition"]
    Composition --> API["gateway_channel_api"]
    Composition --> Config["gateway_config"]
    Composition --> FileAdapter["gateway_channel_file_adapter"]
    Composition --> RadioAdapter["gateway_channel_radio_adapter"]
    API --> Application["gateway_channel_application"]
    FileAdapter --> Application
    RadioAdapter --> Application
    Application --> Domain["gateway_channel_domain"]
```

The API is currently an in-process C++ function-call API. The executable has:

- `once`: initialize or reconcile state, print status, and exit.
- `serve`: reconcile desired and applied state until SIGINT or SIGTERM.
