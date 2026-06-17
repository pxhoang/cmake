# Architecture Overview

The project uses feature-oriented Clean Architecture inside each binary.
Architectural layers are separate CMake targets, so forbidden dependencies fail
at compile time instead of relying only on directory conventions.

## Gateway Device Feature

The current sample feature is `device`. It is intentionally small, but it uses
the same layout expected for future features:

```text
src/apps/gateway_service/features/device/
├── domain/          # Pure business types and rules
├── application/     # Use cases and ports
├── api/             # In-process input adapter used by the service
└── adapters/        # External side-effect adapters
    ├── console/
    └── persistence/
        └── file/
```

`application` owns the ports:

- `DeviceStateRepository`: persistence port.
- `DeviceController`: external device-control port.

Outer layers implement those ports:

- `adapters/persistence/file/FileDeviceStateRepository`
- `adapters/console/ConsoleDeviceController`

`bootstrap` is the composition root. It is the only place that should know
about both use cases and concrete adapters.

At the C++ symbol level, gateway-service-owned types share one namespace:
`gateway_service`. The directory structure still represents layers and feature
ownership, but those folders are not mirrored as nested C++ namespaces.

## Target Graph

```mermaid
graph TD
    Service["gateway_service"] --> Composition["gateway_composition"]
    Composition --> API["gateway_device_api"]
    Composition --> Config["gateway_config"]
    Composition --> Persistence["gateway_device_file_persistence"]
    Composition --> ConsoleAdapter["gateway_device_console_adapter"]
    API --> Application["gateway_device_application"]
    Persistence --> Application
    ConsoleAdapter --> Application
    Application --> Domain["gateway_device_domain"]
```

The API is currently an in-process C++ function-call API. The executable has:

- `once`: initialize or reconcile state, print status, and exit.
- `serve`: reconcile desired and applied state until SIGINT or SIGTERM.

## Layer Meaning

| Layer | Responsibility | May depend on |
|-------|----------------|---------------|
| `domain` | Business types and invariants | Nothing project-specific |
| `application` | Use cases and ports | `domain` |
| `api` | Input adapter for callers inside the process | `application` |
| `adapters` | External mechanisms, including persistence | `application` ports |
| `bootstrap` | Object graph composition | Concrete outer layers |

Persistence code belongs under `adapters/persistence/`. The application layer
owns storage ports, and concrete storage implementations are adapter details.
