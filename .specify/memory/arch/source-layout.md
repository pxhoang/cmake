# Architecture: Source Layout

Repository areas are fixed. Files MUST be placed in the narrowest matching
area.

```text
src/apps/           Executable applications and app-owned feature slices
src/libs/           Internal reusable libraries
tests/              Cross-component integration and end-to-end tests
tooling/            CMake modules, scripts, Docker, and dependency metadata
ops/                Runtime configuration and deployment assets
.specify/memory/    Binding constitutional memory
.specify/templates/ Spec Kit templates
.github/workflows/  CI workflow definitions
.img/               Generated build, package, runtime, and downloaded output
```

Root-level files MUST be limited to project identity, build entry points, and
repository-wide configuration, such as `README.md`, `LICENSE`,
`CMakeLists.txt`, `CMakePresets.json`, `.gitignore`, `.editorconfig`,
`.clang-format`, `.clang-tidy`, and `.dockerignore`.

## Test Placement

1. App-owned unit tests SHOULD live beside the relevant app test tree.
2. Cross-component integration tests MUST live under `tests/integration/`.
3. End-to-end tests MUST live under `tests/e2e/`.

## Dot Directories

Local editor, cache, Git, Codex, and agent metadata MAY live in dot-directories
such as `.git/`, `.vscode/`, `.cache/`, `.codex/`, and `.agents/`.

Product source, tests, deployment assets, tooling, and memory MUST NOT be
hidden inside local metadata directories.

## Generated Output

Generated build, package, runtime, test scratch, and downloaded output MUST
stay under `.img/`.

## Required Evidence

Plans and reviews that add, move, or generate files MUST state:

1. The repository area for each affected path.
2. Whether each affected path is source, test, tooling, ops, memory,
   `.specify/`, CI, or generated output.
3. The `.img/` location for generated output.
4. The reason any new root-level file is allowed.
