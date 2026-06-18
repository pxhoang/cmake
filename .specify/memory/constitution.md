<!--
Sync Impact Report
Version change: 1.7.0 -> 2.0.0
Modified principles:
- Made `.specify/memory/` the self-contained constitutional authority.
- Grouped architecture, development, and operations rules into focused memory
  folders and files.
- Removed non-memory authority dependencies for constitutional gates.
Added sections:
- Core Principles
- Non-Negotiable Gates
- Required Spec Kit Checks
- Memory Map
Removed sections:
- External normative references.
Templates requiring updates:
- Pending: `.specify/templates/spec-template.md`, add required specification
  impact fields from this constitution.
- Pending: `.specify/templates/plan-template.md`, replace the generic
  Constitution Check placeholder with the required gate checklist.
- Pending: `.specify/templates/tasks-template.md`, enforce constitutional task
  ordering and exact file paths.
- Pending: `.specify/templates/checklist-template.md`, require memory-derived
  checks and non-negotiable gate handling.
Follow-up TODOs:
- Align `.specify/templates/` with this memory set before generating new
  feature artifacts.
-->

# Project Constitution

## 1. Scope

This constitution governs every application, feature, library, test,
operational asset, tool, package, generated Spec Kit artifact, review, audit,
and memory file in this repository.

The project is a Clean C++ service repository. It uses feature-oriented Clean
Architecture, CMake target boundaries, explicit test layers, Linux-aware
systems engineering, operational assets under `ops/`, constitutional memory
under `.specify/memory/`, and generated output under `.img/`.

All product work MUST follow this constitution unless the constitution is
amended.

## 2. Constitutional Force

Rules in `.specify/memory/` are binding project memory:

1. `MUST`, `MUST NOT`, `forbidden`, and `required` rules are non-negotiable.
2. A specification, plan, task list, checklist, implementation, review, or
   generated artifact that violates a non-negotiable rule is blocked.
3. Non-negotiable rules can change only by explicit human approval and a
   documented amendment to the owning memory file.
4. `SHOULD` rules are expected defaults. Deviations require explicit rationale,
   impact, and verification evidence.
5. Generated suggestions, local shortcuts, and agent preferences never
   override `.specify/memory/`.

## 3. Core Principles

### I. Feature-Oriented Clean Architecture

Feature code MUST live inside the owning feature slice. Business rules belong
in `domain` and `application/services`. External mechanisms belong in `api`,
`adapters`, app-level infrastructure, or `bootstrap`.

Concrete implementations MUST be wired only at composition boundaries.

### II. Dependency Direction and CMake Boundaries

Dependencies MUST point inward. Inner layers own policy; outer layers own
mechanisms. Every layer MUST have a narrow CMake target that exposes only the
include directories and dependencies required by its contract.

Targets, include paths, and tests MUST enforce the same architecture graph.
Broad include paths, parent-relative includes across architecture boundaries,
and target dependencies that bypass the layer graph are forbidden.

### III. Explicit Behavior and Verification

Boundary behavior MUST be explicit. Input validation, errors, persistence,
configuration, observability, security, shutdown, and runtime failure modes
must be stated before implementation when affected.

Behavioral changes MUST include tests at the lowest layer that can prove the
behavior. Plans and reviews MUST report verification commands or the blocker
and residual risk.

### IV. C++ and Linux Systems Safety

Project-owned C++ MUST follow the Google C++ Style Guide plus this memory set.
Ownership MUST be explicit, resources MUST use RAII, concurrency MUST be
bounded and testable, Linux runtime behavior MUST be designed deliberately,
and security-sensitive material MUST never be committed.

### V. Operational, Memory, and Generated Output Separation

Operational assets belong under `ops/`; constitutional memory belongs under
`.specify/memory/`; generated build, package, runtime, test scratch, and
downloaded output belongs under `.img/`.

Binding gates live only in `.specify/memory/`.

## 4. Non-Negotiable Gates

Every specification, plan, task list, checklist, implementation, and review
MUST satisfy these gates:

1. Product scope stays within the approved Clean C++ service model. Scope
   expansion requires explicit specification; architecture model changes
   require constitutional amendment.
2. Feature code follows feature-owned Clean Architecture:
   `domain`, `application/ports`, `application/services`, `api`, `adapters`,
   and `bootstrap`.
3. Source, tests, ops, tooling, CI, root files, dot-directories, `.specify/`,
   and generated output are placed in approved repository areas.
4. Every layer has a narrow CMake target boundary with only direct required
   dependencies.
5. Dependencies point inward; inner layers never depend on concrete adapters,
   infrastructure, IPC frameworks, vendor SDKs, persistence implementations,
   or runtime mechanisms.
6. API, IPC, CLI, plugin, background handler, and service handler code is an
   input adapter and does not own business rules or concrete mechanisms.
7. Long-running work, blocking I/O, retries, polling, workers, and shared
   mutable state have explicit responsiveness and shutdown behavior.
8. Persistence and configuration are accessed through application-owned ports
   or app infrastructure, never directly from domain or application business
   rules.
9. Errors are explicit at boundaries and observable without leaking secrets.
10. Behavior is verified at the lowest appropriate test layer.
11. Build, tooling, packaging, deployment, runtime state, and generated output
    follow the fixed repository layout.
12. Constitutional memory is updated when binding rules change; generated
    artifacts do not define constitutional gates.
13. Security-sensitive material is never committed; external input and new
    communication surfaces receive explicit security review.
14. C++ memory, resource lifetime, thread safety, Linux runtime behavior,
    diagnostics, performance, dependency risk, and code review quality are
    explicitly safe for the change.

Any failed gate blocks progress until the design is revised or this
constitution is amended.

## 5. Required Spec Kit Checks

Every specification MUST state:

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
12. Memory and generated-output separation.
13. Security rules.
14. C++ / Linux systems quality.

Each Constitution Check item MUST include evidence. `PASS` requires the
specific file, target, dependency, test, or design decision that satisfies the
gate. `N/A` is allowed only when the change cannot affect that gate, and the
reason MUST be stated. `FAIL` blocks progress.

Plans with failed gates MUST NOT move to tasks or implementation.

Task lists MUST order work so enforcement comes before implementation:

1. Architecture, target, and repository-placement tasks.
2. Failing tests or documented test updates.
3. Implementation tasks.
4. Memory, operations, tooling, CI, and security updates.
5. Verification tasks.

## 6. Memory Map

Read `.specify/memory/README.md` first when navigating memory.

Architecture memory:

1. `.specify/memory/arch/README.md`
2. `.specify/memory/arch/source-layout.md`
3. `.specify/memory/arch/feature-architecture.md`
4. `.specify/memory/arch/dependencies.md`
5. `.specify/memory/arch/cmake-targets.md`
6. `.specify/memory/arch/api-handlers.md`
7. `.specify/memory/arch/persistence-config.md`
8. `.specify/memory/arch/concurrency.md`
9. `.specify/memory/arch/errors-observability.md`
10. `.specify/memory/arch/security.md`

Development memory:

1. `.specify/memory/dev/README.md`
2. `.specify/memory/dev/cpp-style.md`
3. `.specify/memory/dev/cmake-build.md`
4. `.specify/memory/dev/testing.md`
5. `.specify/memory/dev/memory-ownership.md`
6. `.specify/memory/dev/resource-lifetime.md`
7. `.specify/memory/dev/thread-safety.md`
8. `.specify/memory/dev/linux-platform.md`
9. `.specify/memory/dev/static-analysis.md`
10. `.specify/memory/dev/dependencies-performance.md`
11. `.specify/memory/dev/local-workflow.md`
12. `.specify/memory/dev/review-workflow.md`

Operations memory:

1. `.specify/memory/ops/README.md`
2. `.specify/memory/ops/deployment.md`
3. `.specify/memory/ops/runtime-configuration.md`
4. `.specify/memory/ops/service-operations.md`
5. `.specify/memory/ops/runtime-hardening.md`

If memory files conflict, this constitution wins. If two supporting memory
files conflict, stop and request clarification or an amendment.

## 7. Governance

This constitution overrides informal conventions, generated plans, and agent
preferences. Agents MUST treat it as higher priority than local convenience,
generated suggestions, or inferred framework defaults.

Amendments require explicit human approval and a documented update to the
owning memory file. Any amendment MUST include the reason, expected impact,
migration work, and verification plan. Changes that weaken or remove gates
require a MAJOR version bump. New gates or materially expanded obligations
require a MINOR version bump. Clarifications that do not change obligations
require a PATCH version bump.

Every plan and implementation review MUST check compliance with this
constitution. Non-compliant work MUST be revised before it is considered done.

**Version**: 2.0.0 | **Ratified**: 2026-06-17 | **Last Amended**: 2026-06-18
