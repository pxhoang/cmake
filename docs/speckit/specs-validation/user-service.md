# User Service Spec Validation Sample

This sample shows how an agent should design and validate a new `user_service`
against `docs/speckit/constitution.md`.

This document is not normative. It is a validation artifact for checking
whether agents correctly apply the constitution and the normative guides.

## User Request

```text
Create a user_service that can register a user and read a user profile.
Store users locally for now. Keep the project architecture.
```

## Specification

### Product Scope

`user_service` is a new Clean C++ executable application under `src/apps/`.
It uses an in-process C++ function-call API. No HTTP, TCP, RPC, message bus,
plugin, or background handler surface is introduced.

Scope expansion: N/A. The request stays within the approved Clean C++ service
model.

Architecture model change: N/A. The service follows the required
feature-oriented Clean Architecture.

### Affected Areas

```text
Application: user_service
App prefix: user
Application namespace: user_service
Feature: identity
Layers: domain, application, api, adapters, bootstrap
CMake targets:
- user_identity_domain
- user_identity_ports
- user_identity_services
- user_identity_api
- user_identity_file_persistence
- user_config
- user_composition
- user_service
Repository areas:
- src/apps/user_service/
- src/apps/user_service/tests/unit/
- tests/integration/user_service/
- tests/e2e/user_service/
- ops/config/user_service/
- ops/deploy/
- docs/architecture/
- docs/operations/
```

### User-Visible Behavior

1. Register a user with a valid user name.
2. Read a user profile by user id.
3. Return explicit failure for invalid input, duplicate registration, missing
   user profile, and persistence errors.

### Architecture Impact

The `identity` feature owns user behavior:

```text
src/apps/user_service/features/identity/
|-- domain/
|-- application/
|-- api/
`-- adapters/
    `-- persistence/
        `-- file/
```

Domain types:

1. `UserId`
2. `UserName`
3. `UserProfile`

Application services:

1. `RegisterUserService`
2. `GetUserProfileService`

Application ports:

1. `UserRepository`

Concrete adapters:

1. `FileUserRepository`

API:

1. `UserApi`

Composition root:

1. `bootstrap`

### Dependency Impact

Allowed target graph:

```text
user_service
`-- user_composition
    |-- user_config
    |-- user_identity_api
    |   `-- user_identity_services
    |       `-- user_identity_ports
    |           `-- user_identity_domain
    `-- user_identity_file_persistence
        `-- user_identity_ports
            `-- user_identity_domain
```

Forbidden dependencies:

```text
user_identity_domain -> user_identity_ports
user_identity_domain -> user_identity_services
user_identity_domain -> user_identity_api
user_identity_domain -> user_identity_file_persistence
user_identity_ports -> user_identity_services
user_identity_ports -> user_identity_api
user_identity_ports -> user_identity_file_persistence
user_identity_services -> user_identity_file_persistence
user_identity_api -> user_identity_file_persistence
user_identity_api -> user_config
```

### Persistence and Configuration Impact

`UserRepository` is an application-owned port.
`FileUserRepository` is the local persistence adapter under
`adapters/persistence/file/`.

Configuration examples live under:

```text
ops/config/user_service/
```

The configuration loader lives in app infrastructure and validates required
fields. Domain and application layers do not read files, environment variables,
or process state directly.

### Security Impact

No secrets are committed. Example configuration uses non-secret placeholders.
User names, user ids, config values, and file paths are treated as untrusted
input until validated.

New external communication surface: N/A. If a future plan adds HTTP or another
IPC surface, it must include authentication, authorization, validation,
timeouts, failure modes, and target boundaries.

### Observability and Error Handling Impact

Failures are explicit at boundaries:

1. Invalid user name or id.
2. Duplicate user.
3. Missing user profile.
4. File persistence failure.
5. Configuration parse failure.

Domain code does not log, print, write files, emit metrics, or terminate the
process.

### Testability Impact

Unit tests cover domain, application services, API translation, and config
parsing. Application tests use fake repositories. API tests do not link
concrete persistence.

Integration tests cover file persistence and bootstrap wiring.

End-to-end tests cover executable behavior.

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
|-- features/
|   `-- identity/
|       |-- CMakeLists.txt
|       |-- domain/
|       |   |-- CMakeLists.txt
|       |   |-- user_id.hpp
|       |   |-- user_name.hpp
|       |   `-- user_profile.hpp
|       |-- application/
|       |   |-- CMakeLists.txt
|       |   |-- get_user_profile_service.hpp
|       |   |-- register_user_service.hpp
|       |   `-- user_repository.hpp
|       |-- api/
|       |   |-- CMakeLists.txt
|       |   |-- user_api.cpp
|       |   `-- user_api.hpp
|       `-- adapters/
|           |-- CMakeLists.txt
|           `-- persistence/
|               |-- CMakeLists.txt
|               `-- file/
|                   |-- CMakeLists.txt
|                   |-- file_user_repository.cpp
|                   `-- file_user_repository.hpp
`-- tests/
    `-- unit/
        |-- app_config_test.cpp
        |-- get_user_profile_service_test.cpp
        |-- register_user_service_test.cpp
        |-- user_api_test.cpp
        `-- user_domain_test.cpp
```

Cross-component tests:

```text
tests/integration/user_service/
|-- bootstrap_test.cpp
`-- file_user_repository_test.cpp

tests/e2e/user_service/
`-- run_user_service_test.sh
```

Ops assets:

```text
ops/config/user_service/
|-- config.example.json
`-- example.env

ops/deploy/systemd/user_service.service
ops/deploy/package/user_service/
```

## Constitution Check

| Gate | Result | Evidence |
|------|--------|----------|
| Product scope | PASS | New executable `user_service` remains a Clean C++ service with in-process API only. |
| Architecture principles | PASS | Feature code is under `src/apps/user_service/features/identity/` with `domain`, `application`, `api`, `adapters`, and `bootstrap`. |
| Source layout and layering | PASS | Product source, unit tests, integration tests, e2e tests, ops assets, and docs are placed in approved repository areas listed above. |
| CMake target boundaries | PASS | Proposed targets are `user_identity_domain`, `user_identity_ports`, `user_identity_services`, `user_identity_api`, `user_identity_file_persistence`, `user_config`, `user_composition`, and `user_service`. |
| Dependency rules | PASS | Target graph points inward; concrete persistence is linked only by `user_composition`. |
| API / IPC / handler rules | PASS | `UserApi` is an input adapter and does not include or link `FileUserRepository`; no external IPC is introduced. |
| Responsiveness and concurrency | PASS | No worker, detached thread, polling loop, or blocking service loop is introduced; file I/O stays in the adapter. |
| Persistence and configuration | PASS | `UserRepository` is an application port; `FileUserRepository` is under `adapters/persistence/file`; config examples live under `ops/config/user_service/`. |
| Error handling and observability | PASS | Invalid input, duplicate user, missing profile, persistence failure, and config parse failure are explicit; domain has no I/O or logging. |
| Testing requirements | PASS | Unit, integration, and e2e test files are planned in the approved locations; application tests use fakes. |
| Build, tooling, and packaging | PASS | No new shared tooling is required; deploy/package assets are under `ops/deploy/`; generated output remains under `.img/`. |
| Documentation separation | PASS | Architecture docs go under `docs/architecture/`; operations docs go under `docs/operations/`; this sample lives under `docs/speckit/specs-validation/`. |
| Security rules | PASS | No secrets are committed; user input, config values, and file paths are validated; no external communication surface is introduced. |

Result: PASS. The design may proceed to task planning.

## Task Plan

Tasks are ordered so enforcement comes before implementation.

```text
1. Add `src/apps/user_service/` CMake skeleton and layer targets.
2. Add failing unit tests for domain values, services, API translation, and
   config parsing.
3. Add failing integration tests for file persistence and bootstrap wiring.
4. Add failing e2e executable-flow test.
5. Implement `identity/domain` value types.
6. Implement `identity/application` ports and services.
7. Implement `identity/api` input adapter.
8. Implement `identity/adapters/persistence/file` repository.
9. Implement app config loader under `infrastructure/config`.
10. Wire concrete adapters only in `bootstrap`.
11. Add ops config examples, systemd unit, package docs, and operations docs.
12. Run `./tooling/scripts/test.sh`.
```

## Non-Compliant Agent Output

The following agent output must be rejected:

```text
Implement user registration directly in src/apps/user_service/main.cpp.
Read and write users directly from UserApi.
Add HTTP handlers in application/services for convenience.
Skip CMake targets until the feature works.
Store temporary user database files under tests/tmp/.
Commit a config file with a real token.
```

Constitution failures:

1. Architecture principles: FAIL. Feature layers are skipped.
2. CMake target boundaries: FAIL. No layer targets enforce dependencies.
3. Dependency rules: FAIL. API/application depend on concrete persistence.
4. API / IPC / handler rules: FAIL. HTTP surface is introduced without adapter
   boundary or security review.
5. Build, tooling, and packaging: FAIL. Generated runtime/test output is
   outside `.img/`.
6. Security rules: FAIL. Secret material is committed.

Expected agent behavior: stop, reject the design, and revise until every gate
is PASS with evidence.
