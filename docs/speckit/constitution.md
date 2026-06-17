<!--
Sync Impact Report
Version change: 1.2.1 -> 1.3.0
Modified principles:
- Reorganized constitution into the recommended 14-section structure
- Expanded rules for product scope, API/IPC/handlers, responsiveness,
  persistence/configuration, error handling/observability, and security
- Preserved existing Clean Architecture, CMake, repository layout, testing,
  tooling, documentation, generated-output, and governance rules
Added sections:
- Product Scope
- API / IPC / Handler Rules
- Responsiveness and Concurrency
- Persistence and Configuration
- Error Handling and Observability
- Security Rules
Removed sections:
- Core Principles
- Architecture Boundaries
- Repository Area Gates
- Artifact Requirements
- Quality Gates
Templates requiring updates:
- Pending: .specify/memory/constitution.md, replace with this constitution
- Pending: .specify/templates/spec-template.md, require scope, architecture,
  repository area, security, error handling, and testability impact
- Pending: .specify/templates/plan-template.md, require the Constitution Check
  gates from this document
- Pending: .specify/templates/tasks-template.md, require architecture,
  repository-placement, test, documentation, ops, tooling, and verification
  tasks before implementation is considered complete
Follow-up TODOs: None
-->

# Project Constitution

## 1. Product Scope

This repository is a Clean C++ service project. It demonstrates and enforces a
feature-oriented Clean Architecture for executable applications, internal
libraries, cross-component tests, operational assets, engineering tooling, and
documentation.

The reference application is `gateway_service`. Its current API is an
in-process C++ function-call API. TCP, HTTP, message bus, RPC, plugin, or other
IPC surfaces are outside the default product scope and MUST NOT be introduced
without an explicit specification, architecture impact statement, tests, and
constitutional compliance check.

The product scope includes:

1. Executable applications under `src/apps/`.
2. Internal reusable libraries under `src/libs/`.
3. Runtime configuration and deployment assets under `ops/`.
4. Developer, CI, build, Docker, and packaging tooling under `tooling/`.
5. Unit, integration, and end-to-end tests.
6. Architecture, development, operations, ADR, and Spec Kit documentation.

Generated build, package, runtime, and downloaded output is not product source
and MUST stay under `.img/`.

## 2. Architecture Principles

Every application feature MUST be implemented as a feature-owned Clean
Architecture slice. Business rules belong in inner layers. External mechanisms
belong in outer layers. Dependencies MUST point inward.

Required feature shape:

```text
src/apps/<app>/features/<feature>/
|-- domain/
|-- application/
|-- api/
`-- adapters/
    |-- console/
    `-- persistence/
```

Layer responsibilities:

1. `domain`: pure business types, invariants, and rules.
2. `application`: use cases and ports.
3. `api`: in-process input adapters for callers.
4. `adapters`: external mechanisms and side effects.
5. `bootstrap`: composition root for wiring concrete implementations.

Agents MUST NOT flatten feature layers, skip ports, place business logic in
adapters, wire concrete implementations outside `bootstrap`, or create a
temporary monolith. A different architecture requires a constitutional
amendment before implementation.

For this repository, `gateway_service` is the reference implementation:

```text
src/apps/gateway_service/features/device/
```

## 3. Source Layout and Layering

Repository areas are fixed:

```text
src/apps/          Executable applications and app-owned feature slices
src/libs/          Internal reusable libraries
tests/             Cross-component integration and end-to-end tests
tooling/           CMake modules, scripts, Docker, and dependency metadata
ops/               Runtime configuration and deployment assets
docs/              Architecture, development, operations, ADR, and Spec Kit docs
.github/workflows/ CI workflow definitions
.img/              Generated build, package, runtime, and downloaded output
```

Root-level files MUST be limited to project identity, build entry points, and
repository-wide configuration, such as `README.md`, `LICENSE`,
`CMakeLists.txt`, `CMakePresets.json`, `.gitignore`, `.editorconfig`,
`.clang-format`, `.clang-tidy`, and `.dockerignore`.

Documentation subdirectories are fixed:

```text
docs/adr/           Architecture decisions
docs/architecture/  Architecture overview and dependency rules
docs/development/   Build, test, and local development guidance
docs/operations/    Deployment and runtime operations guidance
docs/speckit/       Spec Kit constitution and validation artifacts
```

Test placement is scope-based:

1. App-owned unit tests SHOULD live beside the relevant app test tree.
2. Cross-component integration tests MUST live under `tests/integration/`.
3. End-to-end tests MUST live under `tests/e2e/`.

Local editor, cache, Git, Codex, and agent metadata MAY live in dot-directories
such as `.git/`, `.vscode/`, `.cache/`, `.codex/`, and `.agents/`, but product
source, tests, deployment assets, tooling, and documentation MUST NOT be hidden
inside those directories. CI configuration is the exception and belongs in
`.github/workflows/`.

Each application MUST use one shared application namespace for public
application-owned C++ types. Directory boundaries express architecture layers;
they MUST NOT be mirrored as nested C++ namespaces. For this repository, the
shared namespace is `gateway_service`.

## 4. CMake Target Boundaries

CMake targets are architecture boundaries. Every layer MUST be represented by a
narrow target that exposes only the include directories and dependencies
required by that layer contract.

New feature targets MUST follow an app-specific prefix derived from the
executable or application target name. For an app prefix named `<app_prefix>`,
targets MUST follow this style:

```text
<app_prefix>_<feature>_domain
<app_prefix>_<feature>_application
<app_prefix>_<feature>_api
<app_prefix>_<feature>_<adapter>_adapter
<app_prefix>_<feature>_<persistence>_persistence
<app_prefix>_composition
```

For this repository, the app prefix is `gateway`, producing targets such as
`gateway_device_domain`, `gateway_device_application`,
`gateway_device_api`, `gateway_device_file_persistence`, and
`gateway_composition`.

Agents MUST update the closest `CMakeLists.txt` files beside affected source.
Shared CMake behavior MUST go in `tooling/cmake/` only when it is reusable
across targets. Parent-relative includes, broad public include paths, or target
dependencies that bypass layer rules are forbidden.

## 5. Dependency Rules

Allowed dependencies:

```text
api -> application
application -> domain
adapters -> application ports
adapters/persistence -> application ports
bootstrap -> concrete outer layers
```

Forbidden dependencies:

```text
domain -> api
domain -> adapters
domain -> infrastructure
application -> concrete adapter implementations
application -> external vendor SDK
api -> concrete adapter implementations
api -> persistence implementations
```

Ports for external state, devices, services, and infrastructure MUST be defined
in `application`. Concrete implementations MUST be defined in `adapters/` or
app-level infrastructure where appropriate, and wired only by `bootstrap`.

Any specification, plan, or task list that changes product code MUST state the
affected application, feature, layer, CMake target, and dependency impact. If a
change crosses a layer boundary, the artifact MUST explain why the dependency
remains legal.

## 6. API / IPC / Handler Rules

The default application API is an in-process C++ function-call API. API code is
an input adapter. It translates caller input into application use case calls
and translates use case output into caller-facing responses.

API, IPC, and handler code MUST:

1. Depend on application use cases, not concrete adapters.
2. Keep protocol parsing and formatting outside domain and application logic.
3. Validate caller input at the boundary before invoking use cases.
4. Avoid owning business rules, persistence rules, retry policies, or device
   mechanism details.
5. Return explicit success or failure information; it MUST NOT hide operational
   failures behind default values.

New TCP, HTTP, RPC, message bus, CLI command router, plugin, or background
handler surfaces MUST be introduced as adapters with explicit ports, tests,
configuration, security considerations, and CMake target boundaries. They MUST
NOT be added directly inside domain or application code.

## 7. Responsiveness and Concurrency

Long-running applications MUST remain responsive to shutdown signals and
operational failure. For service-style code, SIGINT and SIGTERM handling MUST
be considered in the plan when loops, waits, worker threads, or blocking I/O
are introduced.

Concurrency rules:

1. Domain types MUST remain pure and free of thread, sleep, timer, file,
   process, socket, and environment dependencies.
2. Application use cases MUST not create detached threads or unbounded
   background work.
3. Blocking I/O belongs in adapters or app-level infrastructure and MUST have a
   bounded behavior or documented shutdown path.
4. Shared mutable state MUST be protected by clear ownership, synchronization,
   or confinement.
5. Retry, polling, and reconciliation loops MUST have explicit stop conditions
   and test coverage for failure or shutdown behavior.

Concurrency primitives are allowed only where they are part of the mechanism or
orchestration being implemented. They MUST NOT be used to bypass architecture
boundaries.

## 8. Persistence and Configuration

Persistence ports MUST be owned by the `application` layer. Persistence
implementations MUST live under `adapters/persistence/`. Persistence code MUST
not introduce business rules that belong in domain or application use cases.

Configuration rules:

1. Runtime configuration examples and defaults MUST live under `ops/config/`.
2. Deployment configuration MUST live under `ops/deploy/`.
3. Application configuration loading may live in app-level infrastructure, but
   domain and application layers MUST NOT read files, environment variables, or
   process state directly.
4. Configuration parsing MUST validate required fields and report actionable
   errors.
5. Secrets, credentials, private keys, tokens, and machine-local paths MUST NOT
   be committed.

Generated runtime state, test output, package output, downloaded dependencies,
and build output MUST stay under `.img/`.

## 9. Error Handling and Observability

Errors MUST be explicit at layer boundaries. Domain and application code MUST
not silently swallow failures from ports or adapters. Adapter failures MUST be
translated into application-visible errors without leaking mechanism-specific
details into domain types.

Error handling rules:

1. Validate input at API, configuration, persistence, and external mechanism
   boundaries.
2. Preserve enough context for debugging without exposing secrets.
3. Use exceptions, result types, or status objects consistently with nearby
   code.
4. Do not use process termination, global state mutation, or logging as a
   substitute for returning an error from reusable code.

Observability rules:

1. User-facing command output and service logs MUST describe meaningful state
   transitions and failures.
2. Domain logic MUST not write to stdout, stderr, logs, files, or metrics.
3. Observability mechanisms belong in API, adapters, bootstrap, or app-level
   infrastructure.
4. Tests that depend on output MUST assert stable behavior, not incidental
   formatting unless formatting is the contract.

## 10. Testing Requirements

Behavioral changes MUST include tests at the lowest layer that can prove the
behavior.

Required testing rules:

1. Domain behavior MUST be covered by domain-level unit tests.
2. Application use cases MUST be tested with fakes for ports and MUST NOT link
   concrete adapter implementations.
3. API behavior MUST be tested without depending on concrete persistence or
   device adapters.
4. Adapter tests MUST verify mechanism behavior without moving business rules
   into adapters.
5. Bootstrap, persistence, and cross-component wiring belong in integration
   tests.
6. Executable flows belong in end-to-end tests when user-visible behavior or
   deployment behavior changes.

Agents MUST identify the tests expected to fail before the change and pass
after the change. If the change is documentation-only, the plan MUST state that
no code verification is required.

The preferred full verification command is:

```bash
./tooling/scripts/test.sh
```

For shared architecture, CMake, target wiring, or cross-component behavior,
agents MUST run the full verification command unless blocked. If verification
cannot run, the final report MUST include the exact command, failure reason,
and residual risk.

## 11. Build, Tooling, and Packaging

Build and tooling assets MUST stay in their fixed areas:

```text
tooling/cmake/      Shared CMake modules and dependency declarations
tooling/docker/     Docker build and development environment files
tooling/scripts/    Developer and CI command entry points
.github/workflows/  CI workflow definitions
```

Packaging and deployment assets MUST stay under `ops/deploy/`. Runtime
configuration examples MUST stay under `ops/config/`.

Generated build directories such as `build/`, `cmake-build-*`, compiler
outputs, logs, package output, downloaded dependency output, and runtime
scratch files MUST NOT be placed outside `.img/`. Agents MUST NOT commit
generated output unless a human explicitly requests it.

Tooling changes MUST preserve existing command entry points unless the plan
documents a migration and updates README/development docs. Reusable build
logic belongs in `tooling/cmake/`; one-off target configuration belongs beside
the target in its nearest `CMakeLists.txt`.

## 12. Documentation Separation

Documentation MUST be separated by purpose:

```text
docs/adr/           Architecture decisions
docs/architecture/  Architecture overview and dependency rules
docs/development/   Build, test, and local development guidance
docs/operations/    Deployment and runtime operations guidance
docs/speckit/       Spec Kit constitution and validation artifacts
```

Documentation changes MUST be placed in the narrowest matching documentation
area. Architecture changes require an update to `docs/architecture/` or
`docs/adr/`. Build and local workflow changes require `docs/development/`.
Runtime, service, package, and deployment changes require `docs/operations/`.
Spec Kit constitution, validation, and planning artifacts belong only in
`docs/speckit/`.

Documentation MUST describe actual behavior and enforced rules. It MUST NOT
document architecture exceptions that are not approved by governance.

## 13. Security Rules

Security-sensitive material MUST NOT be committed. This includes credentials,
tokens, private keys, production secrets, personal machine paths, and private
runtime state.

Security rules:

1. Treat file paths, environment variables, config files, IPC messages, and
   external input as untrusted until validated.
2. Do not log secrets or full sensitive configuration values.
3. Keep permissions, ownership, systemd, package, and deployment behavior in
   `ops/` and document operational impact.
4. New external communication surfaces MUST include authentication,
   authorization, input validation, timeout, and failure-mode considerations in
   the plan.
5. Dependency additions MUST be explicit, justified, and isolated behind the
   correct layer or library boundary.
6. Test fixtures MUST use non-secret sample data.

Security shortcuts, temporary plaintext secrets, and local-only assumptions are
non-compliant unless explicitly approved by constitutional amendment.

## 14. Governance

This constitution overrides informal conventions, generated plans, and agent
preferences. Agents MUST treat it as higher priority than local convenience,
generated suggestions, or inferred framework defaults.

Every specification MUST include:

1. Product scope impact.
2. Affected application, feature, layer, CMake target, and repository area.
3. User-visible behavior or operational outcome.
4. Architecture, dependency, persistence, configuration, security,
   observability, and testability impact.

Every plan MUST include a Constitution Check with PASS, FAIL, or N/A for:

1. Product scope.
2. Architecture principles.
3. Source layout and layering.
4. CMake target boundaries.
5. Dependency rules.
6. API / IPC / handler rules.
7. Responsiveness and concurrency.
8. Persistence and configuration.
9. Error handling and observability.
10. Testing requirements.
11. Build, tooling, and packaging.
12. Documentation separation.
13. Security rules.

Plans with failed gates MUST NOT move to tasks or implementation. The agent
MUST revise the design until every gate passes or request a constitutional
amendment.

Task lists MUST order work so enforcement comes before implementation:

1. Architecture, target, and repository-placement tasks.
2. Failing tests or documented test updates.
3. Implementation tasks.
4. Documentation, ops, tooling, CI, and security updates.
5. Verification tasks.

Amendments require explicit human approval and a documented update to this
file. Any amendment MUST include the reason, expected impact, migration work,
and verification plan. Changes that weaken or remove architecture gates require
a MAJOR version bump. New principles or materially expanded requirements
require a MINOR version bump. Clarifications that do not change obligations
require a PATCH version bump.

Every plan and implementation review MUST check compliance with this
constitution. Non-compliant work MUST be revised before it is considered done.

**Version**: 1.3.0 | **Ratified**: 2026-06-17 | **Last Amended**: 2026-06-18
