# Spec Kit Constitution Greenfield Validation

This document validates whether `docs/speckit/constitution.md` can guide a new
project from scratch into the same architecture used by this repository.

## Greenfield Assumption

Sample new project:

```text
Application: gateway_service
App prefix: gateway
Feature: device
Namespace: gateway_service
```

The constitution should force a new project to create this structure:

```text
src/
|-- apps/
|   `-- gateway_service/
|       |-- CMakeLists.txt
|       |-- main.cpp
|       |-- bootstrap/
|       |   |-- CMakeLists.txt
|       |   |-- bootstrap.cpp
|       |   `-- bootstrap.hpp
|       `-- features/
|           `-- device/
|               |-- CMakeLists.txt
|               |-- domain/
|               |   `-- CMakeLists.txt
|               |-- application/
|               |   `-- CMakeLists.txt
|               |-- api/
|               |   `-- CMakeLists.txt
|               `-- adapters/
|                   |-- CMakeLists.txt
|                   |-- console/
|                   |   `-- CMakeLists.txt
|                   `-- persistence/
|                       |-- CMakeLists.txt
|                       `-- file/
|                           `-- CMakeLists.txt
|-- libs/
`-- tests/
```

Generated output belongs under `.img/`. Tooling belongs under `tooling/`.
Runtime configuration and deployment assets belong under `ops/`. Documentation
belongs under `docs/`, with Spec Kit artifacts under `docs/speckit/`.

## Expected CMake Target Graph

A compliant greenfield project must produce this dependency graph:

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

Allowed feature target dependencies:

```text
gateway_device_application -> gateway_device_domain
gateway_device_api -> gateway_device_application
gateway_device_console_adapter -> gateway_device_application
gateway_device_file_persistence -> gateway_device_application
gateway_composition -> gateway_device_api
gateway_composition -> gateway_device_console_adapter
gateway_composition -> gateway_device_file_persistence
```

Forbidden greenfield shortcuts:

```text
gateway_device_domain -> gateway_device_api
gateway_device_domain -> gateway_device_file_persistence
gateway_device_application -> gateway_device_file_persistence
gateway_device_api -> gateway_device_file_persistence
```

## Greenfield Constitution Check

| Gate | Expected Result | Greenfield Evidence Required |
|------|-----------------|------------------------------|
| Product scope | PASS | The project is a Clean C++ service-style project; no unplanned IPC surface is introduced. |
| Architecture principles | PASS | Feature exists under `src/apps/<app>/features/<feature>/` with `domain`, `application`, `api`, and `adapters`. |
| Source layout and layering | PASS | Product, tests, docs, ops, tooling, CI, and generated output are placed in constitution-defined areas. |
| CMake target boundaries | PASS | Each layer has its own narrow CMake target and does not expose broad parent include paths. |
| Dependency rules | PASS | CMake target dependencies match the allowed inward graph above. |
| API / IPC / handler rules | PASS | API code is an input adapter that calls application use cases and does not depend on persistence. |
| Responsiveness and concurrency | PASS | Long-running loops, blocking I/O, or workers have shutdown and failure behavior in the plan. |
| Persistence and configuration | PASS | Ports live in `application`; concrete persistence lives in `adapters/persistence`; config assets live in `ops/config`. |
| Error handling and observability | PASS | Boundary failures are explicit and observable without leaking secrets. |
| Testing requirements | PASS | Domain/application/API behavior has unit tests; adapters have integration tests; executable behavior has e2e tests when needed. |
| Build, tooling, and packaging | PASS | Shared tooling stays under `tooling/`; package/deploy assets stay under `ops/deploy`; generated output stays under `.img/`. |
| Documentation separation | PASS | Docs are placed under the correct `docs/` subdirectory, including `docs/speckit/`. |
| Security rules | PASS | Secrets are not committed; new external inputs or communication surfaces include validation and security considerations. |

Validation result: PASS. With version `1.3.0`, the constitution is suitable for
a new project from scratch and still forces the same architecture as the
current project.

## Greenfield Adoption Requirements

A greenfield project governed by this constitution must enforce:

```text
src/apps/<app>/features/<feature>/ layers
inward-only CMake target dependencies
application-owned ports
bootstrap-only concrete adapter wiring
layer-respecting tests
Repository Area Gates for tests, docs, ops, tooling, CI, generated output,
root files, and dot-directories
Spec Kit artifacts under docs/speckit/
```

Temporary architecture violations are not allowed.

## Sample Plan That Must Pass

```markdown
## Summary

Create the first `device` feature for `gateway_service`.

## Architecture Impact

- Application: `gateway_service`
- App prefix: `gateway`
- Feature: `device`
- Namespace: `gateway_service`
- Layers created: `domain`, `application`, `api`, `adapters`,
  `bootstrap`
- CMake targets created:
  - `gateway_device_domain`
  - `gateway_device_application`
  - `gateway_device_api`
  - `gateway_device_console_adapter`
  - `gateway_device_file_persistence`
  - `gateway_composition`

## Constitution Check

1. Feature code is under `src/apps/gateway_service/features/device/`. PASS.
2. Dependencies point inward:
   `api -> application -> domain`,
   `adapters -> application`,
   `bootstrap -> concrete adapters`. PASS.
3. Ports live in `application`; concrete file and console implementations live
   in `adapters`. PASS.
4. Concrete adapters are wired only by `bootstrap`. PASS.
5. Each layer has a separate CMake target. PASS.
6. Unit tests cover domain/application/API behavior; integration tests cover
   file persistence and bootstrap. PASS.
7. Generated output is configured under `.img/`. PASS.
8. Config, deployment, docs, tooling, CI, and security-sensitive material are
   placed according to the constitution. PASS.
```

## Sample Plan That Must Fail

```markdown
## Summary

Create a simple project quickly by placing business logic, file persistence,
and console output in `src/main.cpp`, then split it later.

## Constitution Check

1. Feature code is not under `src/apps/<app>/features/<feature>/`. FAIL.
2. No layer targets exist, so CMake cannot enforce dependencies. FAIL.
3. Business logic depends directly on concrete persistence and console output.
   FAIL.
4. There is no bootstrap-only composition root. FAIL.
```

Expected agent behavior: stop and redesign before implementation. The
constitution does not allow a temporary monolith as a starting point.
