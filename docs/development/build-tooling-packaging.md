# Build, Tooling, and Packaging

Build and tooling assets MUST stay in fixed areas:

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
scratch files MUST NOT be placed outside `.img/`.

Tooling changes MUST preserve existing command entry points unless the plan
documents a migration and updates README/development docs. Reusable build
logic belongs in `tooling/cmake/`; one-off target configuration belongs beside
the target in its nearest `CMakeLists.txt`.

Agents MUST NOT commit generated output unless a human explicitly requests it.
