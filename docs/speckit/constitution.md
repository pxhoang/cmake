<!--
Sync Impact Report
Version change: 1.4.1 -> 1.5.0
Modified principles:
- Scope: clarified that architecture model changes require constitutional
  amendment.
- Required Checks: added explicit PASS/FAIL/N/A evidence requirements.
- Normative References: removed example documents from binding references.
Added sections: None
Removed sections:
- Spec Kit examples and validation from Normative References
- Informative Examples
Templates requiring updates:
- Pending: .specify/memory/constitution.md, replace with this constitution.
- Pending: .specify/templates/spec-template.md, require scope, architecture,
  repository area, security, error handling, and testability impact.
- Pending: .specify/templates/plan-template.md, require the Constitution Check
  gates from this document.
- Pending: .specify/templates/tasks-template.md, require architecture,
  repository-placement, test, documentation, ops, tooling, and verification
  tasks before implementation is considered complete.
Follow-up TODOs: None
-->

# Project Constitution

## 1. Scope

This constitution applies to every application, feature, library, test,
operation asset, tool, package, and document in any project that adopts it.
It governs Clean C++ service projects using feature-oriented Clean
Architecture, CMake target boundaries, explicit testing layers, operational
assets, engineering tooling, and separated documentation.

All applications and features MUST follow the same architecture unless this
constitution is amended.

Generated build, package, runtime, and downloaded output is not product source
and MUST stay under `.img/`.

## 2. Non-Negotiable Gates

Every specification, plan, task list, and implementation MUST satisfy these
gates:

1. Product scope stays within the approved Clean C++ service model. Scope
   expansion requires explicit specification and validation; architecture model
   changes require constitutional amendment.
2. Feature code follows feature-owned Clean Architecture:
   `domain`, `application`, `api`, `adapters`, and `bootstrap`.
3. Source, tests, docs, ops, tooling, CI, root files, dot-directories, and
   generated output are placed in their approved repository areas.
4. Every layer has a narrow CMake target boundary.
5. Dependencies point inward; inner layers never depend on concrete adapters,
   infrastructure, IPC frameworks, vendor SDKs, or persistence implementations.
6. API, IPC, and handler code is an input adapter and does not own business
   rules or concrete mechanisms.
7. Long-running work, blocking I/O, retries, polling, workers, and shared
   mutable state have explicit responsiveness and shutdown behavior.
8. Persistence and configuration are accessed through application-owned ports
   or app infrastructure, never directly from domain or application business
   rules.
9. Errors are explicit at boundaries and observable without leaking secrets.
10. Behavior is verified at the lowest appropriate test layer.
11. Build, tooling, packaging, deployment, and generated output follow the
    fixed repository layout.
12. Documentation is separated by purpose and updated with behavior changes.
13. Security-sensitive material is never committed; external input and new
    communication surfaces receive explicit security review.

Any failed gate blocks implementation until the design is revised or this
constitution is amended.

## 3. Required Checks

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
12. Documentation separation.
13. Security rules.

Each Constitution Check item MUST include evidence. `PASS` requires the
specific file, target, dependency, test, or design decision that satisfies the
gate. `N/A` is allowed only when the change cannot affect that gate, and the
reason MUST be stated. `FAIL` blocks progress.

Plans with failed gates MUST NOT move to tasks or implementation.

Task lists MUST order work so enforcement comes before implementation:

1. Architecture, target, and repository-placement tasks.
2. Failing tests or documented test updates.
3. Implementation tasks.
4. Documentation, ops, tooling, CI, and security updates.
5. Verification tasks.

## 4. Normative References

The following guides are binding. Implementations MUST comply with this
constitution and these documents:

Architecture:

1. `docs/architecture/architecture.md`
2. `docs/architecture/source-layout.md`
3. `docs/architecture/dependency-rules.md`
4. `docs/architecture/cmake-target-boundaries.md`
5. `docs/architecture/api-handler-rules.md`
6. `docs/architecture/persistence-and-config.md`
7. `docs/architecture/concurrency.md`
8. `docs/architecture/error-handling.md`
9. `docs/architecture/observability.md`
10. `docs/architecture/security.md`

Development:

1. `docs/development/cpp-style-guide.md`
2. `docs/development/testing-guide.md`
3. `docs/development/build-tooling-packaging.md`
4. `docs/development/local-development.md`
5. `docs/development/contributing.md`

Operations:

1. `docs/operations/deployment.md`
2. `docs/operations/runtime-configuration.md`
3. `docs/operations/service-operations.md`

If a guide conflicts with this constitution, this constitution wins. If two
guides conflict, stop and request clarification or an amendment.

## 5. Governance

This constitution overrides informal conventions, generated plans, and agent
preferences. Agents MUST treat it as higher priority than local convenience,
generated suggestions, or inferred framework defaults.

Amendments require explicit human approval and a documented update to this
file. Any amendment MUST include the reason, expected impact, migration work,
and verification plan. Changes that weaken or remove gates require a MAJOR
version bump. New gates or materially expanded obligations require a MINOR
version bump. Clarifications that do not change obligations require a PATCH
version bump.

Every plan and implementation review MUST check compliance with this
constitution. Non-compliant work MUST be revised before it is considered done.

**Version**: 1.5.0 | **Ratified**: 2026-06-17 | **Last Amended**: 2026-06-18
