# Development: CMake, Build, Tooling, and Packaging

The build uses target-based CMake with one declarative helper call per target.
Each component owns its sources, includes, dependencies, and tests.

## CMake Rules

1. Put one `CMakeLists.txt` beside each independently buildable component.
2. Keep directory-index files limited to `add_subdirectory()`.
3. Declare every source explicitly; do not use `file(GLOB)`.
4. Link only direct dependencies.
5. Use `PUBLIC` dependencies only when exposed by public headers.
6. Keep executable `main.cpp` thin and move behavior into testable libraries.
7. Link concrete adapters, including persistence, only from a composition
   target.
8. Add or update a unit test with every behavior change.
9. Prefer existing project helper functions over raw CMake target setup.

## Tooling Areas

Build and tooling assets MUST stay in fixed areas:

```text
CMakeLists.txt        Root build entry point
CMakePresets.json     Build/test preset entry point
tooling/cmake/        Reusable CMake modules
tooling/docker/       Docker build and development environment files
tooling/scripts/      Developer and CI command entry points
.github/workflows/    CI workflow definitions
ops/deploy/           Deployment and packaging assets
ops/config/           Runtime configuration examples and defaults
.img/                 Generated output
```

Packaging command entry points belong in developer/CI tooling. Packaging and
deployment assets MUST stay under `ops/deploy/`. Runtime configuration
examples MUST stay under `ops/config/`.

Generated build directories, compiler outputs, logs, package output,
downloaded dependency output, and runtime scratch files MUST NOT be placed
outside `.img/`.

Tooling changes MUST preserve existing command entry points unless the plan
states the migration impact and required follow-up work.

Agents MUST NOT commit generated output unless a human explicitly requests it.

## Required Evidence

Build, tooling, packaging, Docker, or CI plans and reviews MUST state:

1. Entry point command that remains stable.
2. New or changed CMake preset, script, target, or workflow path.
3. Generated output location under `.img/`.
4. Migration impact when an entry point changes.
5. Verification command or blocker.
