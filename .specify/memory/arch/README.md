# Architecture Memory

This section owns binding architecture rules for source placement, feature
shape, dependency direction, CMake boundaries, APIs, persistence,
configuration, concurrency placement, errors, observability, and security.

## Rule Files

Read the focused file for the affected architecture topic:

1. `source-layout.md`
2. `feature-architecture.md`
3. `dependencies.md`
4. `cmake-targets.md`
5. `api-handlers.md`
6. `persistence-config.md`
7. `concurrency.md`
8. `errors-observability.md`
9. `security.md`

## Section Gates

Architecture work MUST satisfy:

1. Product source, tests, tooling, ops assets, memory, and generated output
   are in approved repository areas.
2. Feature code is contained in the owning feature slice.
3. `domain`, `application/ports`, `application/services`, `api`, `adapters`,
   and `bootstrap` keep their responsibilities.
4. Dependencies point inward.
5. CMake targets enforce architecture boundaries.
6. API, IPC, CLI, plugin, and handler surfaces are input adapters.
7. Persistence and configuration do not leak into domain or application
   business rules.
8. Long-running or blocking behavior has bounded responsiveness and shutdown.
9. Errors and observability are explicit at boundaries and secret-safe.
10. Security-sensitive material is never committed.

## Required Evidence

Architecture plans and reviews MUST cite the focused architecture memory file
that owns each affected rule and provide the evidence required by that file.
