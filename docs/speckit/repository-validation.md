# Spec Kit Constitution Repository Validation

This document validates the current repository against
`docs/speckit/constitution.md` version `1.3.0`.

Validation result: PASS. The current project follows the constitution across
product code, tests, docs, ops, tooling, generated output, CI, and root
configuration.

## Constitution Gates

| Gate | Result | Evidence |
|------|--------|----------|
| Product scope | PASS | The project is a Clean C++ service project with `gateway_service` as the reference application and an in-process API. |
| Architecture principles | PASS | The `device` feature uses `domain`, `application`, `api`, and `adapters` layers with `bootstrap` composition. |
| Source layout and layering | PASS | Product source, tests, docs, ops, tooling, CI, and generated output are placed in constitution-defined areas. |
| CMake target boundaries | PASS | Feature layers and composition are represented by separate CMake targets. |
| Dependency rules | PASS | Dependencies point inward: API and adapters depend on application, application depends on domain, and composition wires concrete adapters. |
| API / IPC / handler rules | PASS | The current API is an in-process input adapter and no unplanned IPC surface is present. |
| Responsiveness and concurrency | PASS | The executable supports one-shot and service modes; long-running reconciliation is owned by the app flow rather than domain code. |
| Persistence and configuration | PASS | Persistence is behind an application port with file persistence as an adapter; runtime configuration examples live under `ops/config/`. |
| Error handling and observability | PASS | Domain code does not own output or mechanism logging; adapter and executable behavior own external effects. |
| Testing requirements | PASS | Unit, integration, and e2e tests exist at the appropriate scopes. |
| Build, tooling, and packaging | PASS | Shared CMake, Docker, scripts, CI, and package/deploy assets live in their fixed areas. |
| Documentation separation | PASS | ADR, architecture, development, operations, and Spec Kit docs are separated by purpose. |
| Security rules | PASS | No committed secrets are part of the reviewed project layout; examples and deployment assets are separated under `ops/`. |

## Repository Areas

| Area | Result | Evidence |
|------|--------|----------|
| `src/apps/` | PASS | Executable application code lives under `src/apps/gateway_service/`. |
| `src/libs/` | PASS | Internal reusable libraries live under `src/libs/common/` and `src/libs/protocol/`. |
| `tests/integration/` | PASS | Cross-component tests live under `tests/integration/gateway_service/`. |
| `tests/e2e/` | PASS | End-to-end executable-flow tests live under `tests/e2e/gateway_service/`. |
| App unit tests | PASS | App-owned unit tests live under `src/apps/gateway_service/tests/unit/`. |
| `docs/adr/` | PASS | Architecture decision records live under `docs/adr/`. |
| `docs/architecture/` | PASS | Architecture overview and dependency rules live under `docs/architecture/`. |
| `docs/development/` | PASS | Build, Docker, and local development guidance live under `docs/development/`. |
| `docs/operations/` | PASS | Deployment and operations guidance lives under `docs/operations/`. |
| `docs/speckit/` | PASS | Spec Kit constitution and validation artifacts live under `docs/speckit/`. |
| `ops/config/` | PASS | Runtime configuration examples live under `ops/config/gateway_service/`. |
| `ops/deploy/` | PASS | Systemd and package deployment assets live under `ops/deploy/`. |
| `tooling/cmake/` | PASS | Shared CMake modules and dependency declarations live under `tooling/cmake/`. |
| `tooling/docker/` | PASS | Docker development and build environment files live under `tooling/docker/`. |
| `tooling/scripts/` | PASS | Developer and CI command entry points live under `tooling/scripts/`. |
| `.github/workflows/` | PASS | CI workflow definitions live under `.github/workflows/`. |
| `.img/` | PASS | Generated build, package, runtime, and downloaded output are isolated under `.img/`. |
| Root files | PASS | Root files are limited to project identity, CMake entry points, presets, and repo-wide configuration. |
| Dot-directories | PASS | Dot-directories contain Git, editor, cache, Codex, or agent metadata; product source and tests remain in constitution-defined areas. |

## Current Layout Snapshot

```text
.
|-- .github/workflows/          CI workflows
|-- .img/                       Generated build/package/runtime output
|-- docs/
|   |-- adr/                    Architecture decisions
|   |-- architecture/           Architecture overview and dependency rules
|   |-- development/            Build, test, and local development guidance
|   |-- operations/             Deployment and runtime operations guidance
|   `-- speckit/                Spec Kit constitution and validation artifacts
|-- ops/
|   |-- config/                 Runtime configuration examples
|   `-- deploy/                 Deployment and package assets
|-- src/
|   |-- apps/                   Executable applications
|   `-- libs/                   Internal reusable libraries
|-- tests/
|   |-- integration/            Cross-component tests
|   `-- e2e/                    End-to-end tests
`-- tooling/
    |-- cmake/                  Shared CMake modules and dependency metadata
    |-- docker/                 Docker environment files
    `-- scripts/                Developer and CI command entry points
```

## Product Architecture Check

The `gateway_service` `device` feature remains the reference implementation:

```text
src/apps/gateway_service/features/device/
|-- domain/
|-- application/
|-- api/
`-- adapters/
    |-- console/
    `-- persistence/file/
```

Feature target dependencies follow the required inward graph:

```text
gateway_device_application -> gateway_device_domain
gateway_device_api -> gateway_device_application
gateway_device_console_adapter -> gateway_device_application
gateway_device_file_persistence -> gateway_device_application
gateway_composition -> concrete outer-layer targets
```

Result: PASS.

## Generated Output Check

Generated output is ignored by Git and isolated under `.img/`:

```text
.img/build/
.img/package/
.img/runtime/
```

The repository root does not contain tracked build directories, package output,
runtime scratch files, compiler outputs, or logs.

Result: PASS.

## Required Constitution Check For Future Plans

Every future plan must include this constitution check:

```markdown
## Constitution Check

- Product scope: PASS/FAIL/N/A
- Architecture principles: PASS/FAIL/N/A
- Source layout and layering: PASS/FAIL/N/A
- CMake target boundaries: PASS/FAIL/N/A
- Dependency rules: PASS/FAIL/N/A
- API / IPC / handler rules: PASS/FAIL/N/A
- Responsiveness and concurrency: PASS/FAIL/N/A
- Persistence and configuration: PASS/FAIL/N/A
- Error handling and observability: PASS/FAIL/N/A
- Testing requirements: PASS/FAIL/N/A
- Build, tooling, and packaging: PASS/FAIL/N/A
- Documentation separation: PASS/FAIL/N/A
- Security rules: PASS/FAIL/N/A
```

If any item is `FAIL`, the agent must stop and revise the plan before
implementation.
