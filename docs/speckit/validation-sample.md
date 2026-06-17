# Spec Kit Constitution Validation Sample

This document validates `docs/speckit/constitution.md` against the current
`gateway_service` `device` feature and shows how an agent should apply the
constitution to a sample Spec Kit plan.

## Sample Feature Under Review

Feature: `device`

Application: `gateway_service`

Source root:

```text
src/apps/gateway_service/features/device/
|-- domain/
|-- application/
|-- api/
`-- adapters/
    |-- console/
    `-- persistence/file/
```

Relevant CMake targets:

```text
gateway_device_domain
gateway_device_application
gateway_device_api
gateway_device_console_adapter
gateway_device_file_persistence
gateway_composition
```

## Passing Constitution Check

| Gate | Result | Evidence |
|------|--------|----------|
| Product scope | PASS | `gateway_service` remains a Clean C++ service with an in-process API. |
| Architecture principles | PASS | `device` has `domain`, `application`, `api`, and `adapters` directories. |
| Source layout and layering | PASS | Product code, tests, docs, ops, tooling, and generated output stay in constitution-defined areas. |
| CMake target boundaries | PASS | Each layer has a separate target with only direct dependencies exposed. |
| Dependency rules | PASS | `gateway_device_application` depends on `gateway_device_domain`; `gateway_device_api`, `gateway_device_console_adapter`, and `gateway_device_file_persistence` depend on `gateway_device_application`. |
| API / IPC / handler rules | PASS | The API is an input adapter and does not link concrete persistence. |
| Responsiveness and concurrency | PASS | Existing service flow handles long-running reconciliation through composition and executable behavior. |
| Persistence and configuration | PASS | `DeviceStateRepository` is an application port; file persistence is an adapter; runtime config examples live under `ops/config/`. |
| Error handling and observability | PASS | Mechanism failures stay outside domain and application business rules. |
| Testing requirements | PASS | Domain, use case, and API unit tests live under `src/apps/gateway_service/tests/unit`; bootstrap and file persistence integration tests live under `tests/integration/gateway_service`; the executable flow has an e2e test under `tests/e2e/gateway_service`. |
| Build, tooling, and packaging | PASS | Shared CMake, scripts, Docker, and package/deploy assets live in their fixed areas. |
| Documentation separation | PASS | Architecture, development, operations, ADR, and Spec Kit docs are separated under `docs/`. |
| Security rules | PASS | Reviewed feature does not introduce secrets, new external inputs, or new external communication surfaces. |

Validation result: PASS. The current `device` feature conforms to the
constitution.

## Sample Spec Kit Plan That Must Pass

```markdown
## Summary

Add a new `status` query to the existing `device` feature so callers can read
desired and applied device state through the in-process API.

## Architecture Impact

- Application: `gateway_service`
- Feature: `device`
- Layers affected: `application`, `api`
- CMake targets affected:
  - `gateway_device_application`
  - `gateway_device_api`
- New adapter: none
- New persistence mechanism: none

## Constitution Check

1. Product scope: in-process API only; no new IPC surface. PASS.
2. Architecture principles: change remains inside the `device` feature slice.
   PASS.
3. Source layout and layering: code stays under the existing feature layers.
   PASS.
4. CMake target boundaries: existing application and API targets are
   sufficient. PASS.
5. Dependency rules: API depends on application; application depends on domain.
   PASS.
6. API / IPC / handler rules: API translates caller input to use case calls.
   PASS.
7. Responsiveness and concurrency: no new loop, worker, or blocking I/O.
   PASS.
8. Persistence and configuration: no new concrete persistence or config.
   PASS.
9. Error handling and observability: status failures remain explicit. PASS.
10. Testing requirements: add/adjust use case and API unit tests before
    implementation. PASS.
11. Build, tooling, and packaging: no tooling or packaging change. N/A.
12. Documentation separation: no documentation change required. N/A.
13. Security rules: no secrets or new external input surface. PASS.
```

Expected agent behavior: proceed to tasks only after every gate is PASS.

## Sample Spec Kit Plan That Must Fail

```markdown
## Summary

Add a `status` query by reading the state file directly from
`device/api/device_api.cpp` because it is simpler than creating a use case.

## Architecture Impact

- Application: `gateway_service`
- Feature: `device`
- Layers affected: `api`, `adapters/persistence`
- CMake targets affected:
  - `gateway_device_api`
  - `gateway_device_file_persistence`

## Constitution Check

1. Product scope: no new IPC surface. PASS.
2. Architecture principles: API reaches into persistence mechanism. FAIL.
3. Source layout and layering: feature files remain under `device`, but layer
   responsibilities are violated. FAIL.
4. CMake target boundaries: would require API to link concrete persistence.
   FAIL.
5. Dependency rules: `gateway_device_api -> gateway_device_file_persistence`
   is forbidden. FAIL.
6. API / IPC / handler rules: API would own persistence behavior. FAIL.
7. Responsiveness and concurrency: no new loop or worker. N/A.
8. Persistence and configuration: persistence mechanism is referenced outside
   bootstrap/application port flow. FAIL.
9. Error handling and observability: file mechanism failures would leak into
   API behavior. FAIL.
10. Testing requirements: application behavior would not be isolated behind
    fakes. FAIL.
11. Build, tooling, and packaging: no tooling or packaging change. N/A.
12. Documentation separation: no documentation change required. N/A.
13. Security rules: no new secrets or communication surface. N/A.
```

Expected agent behavior: stop. The agent MUST revise the design so `api`
depends on `application`, `application` owns a port or use case, and concrete
persistence remains in `adapters/persistence` wired by `bootstrap`. The agent
MUST NOT continue with this plan as a temporary shortcut.

## Task Ordering Sample

A compliant task list for the passing plan starts with architecture and tests:

```markdown
1. Add failing application/API unit tests for the status query.
2. Confirm existing CMake targets are sufficient; update only if a new target
   boundary is needed.
3. Implement or extend the application use case using existing application
   ports.
4. Expose the use case through `device/api`.
5. Run `./tooling/scripts/test.sh tdd` or the narrowest relevant test command.
6. Run `./tooling/scripts/test.sh` if shared behavior or target wiring changed.
```

Implementation tasks that introduce concrete adapters before tests or before
the Constitution Check are non-compliant.
