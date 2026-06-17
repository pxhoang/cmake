# Architecture Overview

Projects governed by this documentation use feature-oriented Clean Architecture
inside each executable application. Architectural layers are separate CMake
targets, so forbidden dependencies fail at compile time instead of relying only
on directory conventions.

Generic binding rules live in:

- `docs/architecture/architecture.md`
- `docs/architecture/dependency-rules.md`
- `docs/architecture/cmake-target-boundaries.md`

## Gateway Device Feature

The current repository includes `gateway_service` and its `device` feature as a
concrete example of the required architecture:

```text
src/apps/gateway_service/features/device/
|-- domain/          # Pure business types and rules
|-- application/     # Use cases and ports
|-- api/             # In-process input adapter used by the service
`-- adapters/        # External side-effect adapters
    |-- console/
    `-- persistence/
        `-- file/
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

```text
gateway_service
`-- gateway_composition
    |-- gateway_config
    |-- gateway_device_api
    |   `-- gateway_device_application
    |       `-- gateway_device_domain
    |-- gateway_device_file_persistence
    |   `-- gateway_device_application
    `-- gateway_device_console_adapter
        `-- gateway_device_application
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
