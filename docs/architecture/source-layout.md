# Source Layout

Repository areas are fixed. Files MUST be placed in the narrowest matching
area.

```text
src/apps/           Executable applications and app-owned feature slices
src/libs/           Internal reusable libraries
tests/              Cross-component integration and end-to-end tests
tooling/            CMake modules, scripts, Docker, and dependency metadata
ops/                Runtime configuration and deployment assets
docs/               Architecture, development, operations, ADR, and Spec Kit docs
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
docs/architecture/  Architecture overview and dependency rules
docs/development/   Build, test, and local development guidance
docs/operations/    Deployment and runtime operations guidance
docs/speckit/       Spec Kit constitution and planning artifacts
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
