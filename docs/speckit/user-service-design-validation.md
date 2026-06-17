# User Service Constitution Design Validation

This document shows how an agent should design and validate a new
`user_service` application against `docs/speckit/constitution.md` version
`1.3.0`.

The goal is to demonstrate the expected agent behavior before implementation:
define scope, choose the architecture, place files, define CMake targets,
state dependencies, plan tests, and block non-compliant shortcuts.

## User Request

```text
Create a new user_service that can register a user and read a user profile.
Store users locally for now. Keep the same architecture as the current project.
```

## Agent Interpretation

The request is a new executable application, not a new feature inside
`gateway_service`.

```text
Application: user_service
App prefix: user
Namespace: user_service
Features:
- identity
```

The initial API remains an in-process C++ function-call API. No HTTP, TCP, RPC,
message bus, plugin system, or background handler is introduced in this design.
Adding any external communication surface would require explicit scope,
security, configuration, timeout, failure-mode, and test coverage.

## Product Design

The `identity` feature supports:

1. Register a user with a validated user name.
2. Read a user profile by user id.
3. Persist users through an application-owned repository port.
4. Use a file-backed persistence adapter for local storage.

Domain rules:

1. `UserId` is a validated domain value.
2. `UserName` is a validated domain value.
3. `UserProfile` is a pure domain type.
4. Domain code does not read files, environment variables, clocks, stdout, or
   persistence adapters.

Application use cases:

1. `RegisterUserUseCase`
2. `GetUserProfileUseCase`

Application ports:

1. `UserRepository`

Adapters:

1. `adapters/persistence/file/FileUserRepository`

API:

1. `UserApi`, an in-process input adapter that validates request input and
   calls application use cases.

Bootstrap:

1. Wires `UserApi`, use cases, and `FileUserRepository`.

## Proposed Source Layout

```text
src/apps/user_service/
|-- CMakeLists.txt
|-- main.cpp
|-- bootstrap/
|   |-- CMakeLists.txt
|   |-- bootstrap.cpp
|   `-- bootstrap.hpp
|-- infrastructure/
|   `-- config/
|       |-- CMakeLists.txt
|       |-- app_config.cpp
|       `-- app_config.hpp
`-- features/
    `-- identity/
        |-- CMakeLists.txt
        |-- domain/
        |   |-- CMakeLists.txt
        |   |-- user_id.hpp
        |   |-- user_name.hpp
        |   `-- user_profile.hpp
        |-- application/
        |   |-- CMakeLists.txt
        |   |-- get_user_profile_use_case.hpp
        |   |-- register_user_use_case.hpp
        |   `-- user_repository.hpp
        |-- api/
        |   |-- CMakeLists.txt
        |   |-- user_api.cpp
        |   `-- user_api.hpp
        `-- adapters/
            |-- CMakeLists.txt
            `-- persistence/
                |-- CMakeLists.txt
                `-- file/
                    |-- CMakeLists.txt
                    |-- file_user_repository.cpp
                    `-- file_user_repository.hpp
```

Supporting repository areas:

```text
src/apps/user_service/tests/unit/
tests/integration/user_service/
tests/e2e/user_service/
ops/config/user_service/
ops/deploy/systemd/
ops/deploy/package/user_service/
docs/architecture/
docs/operations/
docs/development/
```

Generated output remains under `.img/`.

## Proposed CMake Targets

```text
user_service
user_composition
user_config
user_identity_domain
user_identity_application
user_identity_api
user_identity_file_persistence
```

Expected target graph:

```text
user_service
`-- user_composition
    |-- user_config
    |-- user_identity_api
    |   `-- user_identity_application
    |       `-- user_identity_domain
    `-- user_identity_file_persistence
        `-- user_identity_application
```

Allowed target dependencies:

```text
user_identity_application -> user_identity_domain
user_identity_api -> user_identity_application
user_identity_file_persistence -> user_identity_application
user_composition -> user_config
user_composition -> user_identity_api
user_composition -> user_identity_file_persistence
user_service -> user_composition
```

Forbidden target dependencies:

```text
user_identity_domain -> user_identity_api
user_identity_domain -> user_identity_file_persistence
user_identity_application -> user_identity_file_persistence
user_identity_api -> user_identity_file_persistence
user_identity_api -> user_config
```

## Persistence and Configuration

Persistence is behind `UserRepository`, owned by the application layer.
`FileUserRepository` is an adapter under `adapters/persistence/file/`.

Configuration belongs outside domain and application:

```text
ops/config/user_service/config.example.json
ops/config/user_service/example.env
src/apps/user_service/infrastructure/config/
```

The config loader validates required fields and reports actionable errors.
The domain and application layers do not read files or environment variables.

No secrets are committed. Example config uses non-secret placeholder values.

## API / Handler Design

`UserApi` is an in-process input adapter. It may expose C++ methods such as:

```text
RegisterUserResult register_user(RegisterUserRequest request)
GetUserProfileResult get_user_profile(GetUserProfileRequest request)
```

Rules:

1. `UserApi` validates request shape before invoking use cases.
2. `UserApi` depends on `user_identity_application`.
3. `UserApi` does not include or link `FileUserRepository`.
4. `UserApi` does not parse HTTP, manage sockets, or own routing.
5. Result types make failures explicit.

If a future plan adds HTTP handlers, those handlers must be a new adapter with
separate CMake target boundaries and a security review.

## Error Handling and Observability

Expected error behavior:

1. Invalid user id or name fails at the boundary or domain value constructor.
2. Duplicate user registration returns an explicit application failure.
3. Missing user profile returns an explicit not-found result.
4. File persistence errors are translated by the adapter into
   application-visible failures without leaking file implementation details into
   domain types.

Observability belongs in API, adapters, bootstrap, or executable code. Domain
logic does not log, print, write files, or emit metrics.

## Responsiveness and Concurrency

The initial design has no background worker, no detached thread, and no
long-running loop. If `user_service` later gains a service mode, polling,
watchers, or background cleanup, the plan must define shutdown behavior for
SIGINT and SIGTERM before implementation.

File I/O remains inside the persistence adapter and must have bounded,
testable behavior.

## Testing Plan

Unit tests under `src/apps/user_service/tests/unit/`:

1. `user_domain_test.cpp`: validates `UserId`, `UserName`, and `UserProfile`.
2. `register_user_use_case_test.cpp`: uses fake `UserRepository`.
3. `get_user_profile_use_case_test.cpp`: uses fake `UserRepository`.
4. `user_api_test.cpp`: validates API input translation and result mapping
   without concrete persistence.
5. `app_config_test.cpp`: validates config parsing and missing-field errors.

Integration tests under `tests/integration/user_service/`:

1. `file_user_repository_test.cpp`
2. `bootstrap_test.cpp`

End-to-end tests under `tests/e2e/user_service/`:

1. `run_user_service_test.sh`

Verification:

```bash
./tooling/scripts/test.sh
```

## Documentation, Ops, Tooling, and Packaging

Documentation placement:

```text
docs/architecture/   user_service architecture or dependency updates
docs/operations/     user_service deployment and runtime operation notes
docs/development/    build/test workflow updates if commands change
docs/speckit/        this validation artifact
```

Ops placement:

```text
ops/config/user_service/
ops/deploy/systemd/user_service.service
ops/deploy/package/user_service/
```

Tooling changes are not required unless existing scripts cannot discover a new
application under `src/apps/`. Any reusable tooling belongs under
`tooling/scripts/` or `tooling/cmake/`.

## Constitution Check

| Gate | Result | Evidence |
|------|--------|----------|
| Product scope | PASS | New executable `user_service` stays within Clean C++ service scope and uses an in-process API. |
| Architecture principles | PASS | The `identity` feature uses `domain`, `application`, `api`, `adapters`, and `bootstrap`. |
| Source layout and layering | PASS | Source, tests, docs, ops, tooling, CI, and generated output are placed in constitution-defined areas. |
| CMake target boundaries | PASS | Each feature layer has a narrow target with the `user_` app prefix. |
| Dependency rules | PASS | API and persistence depend on application, application depends on domain, and composition wires concrete adapters. |
| API / IPC / handler rules | PASS | `UserApi` is an input adapter and does not depend on concrete persistence or external IPC. |
| Responsiveness and concurrency | PASS | No background worker or long-running loop is introduced; future service mode requires shutdown design. |
| Persistence and configuration | PASS | `UserRepository` is an application port; file persistence is an adapter; config examples live under `ops/config/user_service/`. |
| Error handling and observability | PASS | Invalid input, not-found, duplicate, and persistence failures are explicit; domain has no logging or I/O. |
| Testing requirements | PASS | Unit, integration, and e2e tests are planned at the correct scopes. |
| Build, tooling, and packaging | PASS | Tooling remains under `tooling/`; deploy/package assets are under `ops/deploy/`; output remains under `.img/`. |
| Documentation separation | PASS | Architecture, operations, development, and Spec Kit documentation have separate locations. |
| Security rules | PASS | No secrets are committed; input and config are validated; future external surfaces require security review. |

Result: PASS. The `user_service` design may proceed to task planning.

## Compliant Task Order

```markdown
1. Add user_service CMake directory skeleton and layer targets.
2. Add failing domain, use case, API, config, persistence, bootstrap, and e2e
   tests in the correct locations.
3. Implement `identity/domain` value types.
4. Implement application ports and use cases.
5. Implement `UserApi` as an in-process input adapter.
6. Implement `FileUserRepository` under `adapters/persistence/file`.
7. Implement config loader under app infrastructure.
8. Wire concrete dependencies in `bootstrap`.
9. Add ops config, service, package, and docs updates.
10. Run `./tooling/scripts/test.sh`.
```

## Non-Compliant Design Example

This design must fail:

```text
Put all user registration logic in src/apps/user_service/main.cpp.
Read and write users directly from main.cpp.
Add HTTP routes directly in application code.
Skip CMake layer targets until later.
Store test output under tests/tmp/.
Commit a local config with a real token.
```

Failure reasons:

1. Violates feature-owned Clean Architecture.
2. Bypasses CMake target boundaries.
3. Makes application/API depend on concrete persistence.
4. Introduces an external IPC surface without security and handler rules.
5. Places generated output outside `.img/`.
6. Commits secret material.

Expected agent behavior: stop, reject the design, and rewrite it until every
constitution gate is PASS.
