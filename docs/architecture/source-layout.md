# Source Layout

Repository areas are fixed. Files MUST be placed in the narrowest matching
area.

```text
src/apps/           Executable applications and app-owned feature slices
src/libs/           Internal reusable libraries
tests/              Cross-component integration and end-to-end tests
tooling/            CMake modules, scripts, Docker, and dependency metadata
ops/                Runtime configuration and deployment assets
docs/               Architecture, development, operations, ADR, reviews, and Spec Kit docs
.github/workflows/  CI workflow definitions
.img/               Generated build, package, runtime, and downloaded output
```

Root-level files MUST be limited to project identity, build entry points, and
repository-wide configuration, such as `README.md`, `LICENSE`,
`CMakeLists.txt`, `CMakePresets.json`, `.gitignore`, `.editorconfig`,
`.clang-format`, `.clang-tidy`, and `.dockerignore`.

Documentation subdirectories:

```text
docs/adr/           Architecture decisions
docs/architecture/  Current system invariants, boundaries, and dependency rules
docs/development/   Implementation practices, tooling, tests, and verification
docs/operations/    Deployed runtime behavior, configuration, and runbooks
docs/reviews/       Point-in-time reviews, audits, and completed assessments
docs/speckit/       Spec Kit constitution and planning artifacts
```

## Documentation Ownership

Documentation MUST live in the section that owns the decision being described:

1. `docs/architecture/` owns durable system invariants: layer shape,
   dependency direction, source placement, target boundaries, API and adapter
   boundaries, persistence/configuration placement, security invariants,
   observability placement, log format, and responsiveness requirements.
2. `docs/development/` owns implementation practice: C++ style, memory,
   resource lifetime, thread-safety primitives, CMake usage, local workflow,
   tests, static analysis, debugging, dependency management, performance, and
   code review expectations.
3. `docs/operations/` owns deployed runtime behavior: deployment assets,
   runtime configuration files and environment variables, service-manager
   behavior, runtime paths, permissions, secret delivery, hardening, rollback,
   and operational runbooks.
4. `docs/adr/` owns accepted architecture decisions and their rationale.
5. `docs/reviews/` owns dated reviews and audits. Review findings that become
   durable rules MUST be promoted into `docs/architecture/`,
   `docs/development/`, or `docs/operations/`.
6. `docs/speckit/` owns constitution and specification/planning artifacts.

Durable rules in `docs/architecture/`, `docs/development/`, and
`docs/operations/` are constitutional inputs. `MUST`, `MUST NOT`, `forbidden`,
and `required` rules are non-negotiable unless the owning guide or constitution
is explicitly amended.

When a topic crosses sections, one section MUST own the rule and the other
sections SHOULD link to it instead of restating it. If ownership is unclear,
choose the section that owns the highest-level decision:

```text
Architecture: what must be true about the system.
Development: how engineers implement and verify it.
Operations: how the deployed service is configured, run, and maintained.
```

Test placement:

1. App-owned unit tests SHOULD live beside the relevant app test tree.
2. Cross-component integration tests MUST live under `tests/integration/`.
3. End-to-end tests MUST live under `tests/e2e/`.

Local editor, cache, Git, Codex, and agent metadata MAY live in dot-directories
such as `.git/`, `.vscode/`, `.cache/`, `.codex/`, and `.agents/`, but product
source, tests, deployment assets, tooling, and documentation MUST NOT be hidden
inside those directories. CI configuration belongs in `.github/workflows/`.

Generated build, package, runtime, test scratch, and downloaded output MUST
stay under `.img/`.
