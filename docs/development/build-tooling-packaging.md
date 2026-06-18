# Build, Tooling, and Packaging

Build and tooling changes must preserve reproducible developer and CI entry
points.

## Ownership

This guide owns developer and CI build tooling, package creation commands, and
generated-output rules. Deployed package contents, service-manager behavior,
runtime directories, permissions, and rollback guidance are owned by
`docs/operations/deployment.md`.

## Must

Build and tooling assets MUST stay in fixed areas:

```text
tooling/cmake/      Shared CMake modules and dependency declarations
tooling/docker/     Docker build and development environment files
tooling/scripts/    Developer and CI command entry points
.github/workflows/  CI workflow definitions
```

Packaging command entry points belong in developer/CI tooling. Packaging and
deployment assets MUST stay under `ops/deploy/`. Runtime configuration examples
MUST stay under `ops/config/`.

Generated build directories such as `build/`, `cmake-build-*`, compiler
outputs, logs, package output, downloaded dependency output, and runtime
scratch files MUST NOT be placed outside `.img/`.

Tooling changes MUST preserve existing command entry points unless the plan
documents a migration and updates README/development docs. Reusable build
logic belongs in `tooling/cmake/`; one-off target configuration belongs beside
the target in its nearest `CMakeLists.txt`.

Agents MUST NOT commit generated output unless a human explicitly requests it.

## Should

1. Prefer existing scripts and CMake presets over new ad hoc commands.
2. Keep developer and CI behavior aligned.
3. Keep reusable logic in `tooling/cmake/` or `tooling/scripts/`.

## Workflow

Use existing repository entry points for build, test, run, Docker, and package
creation. Add new entry points only when the existing scripts cannot express
the workflow clearly.

## Verification

Run the affected script, preset, or CI-equivalent command. If the command
cannot run, report the command, blocker, and residual risk.

## Related Guides

- `docs/development/cmake.md`
- `docs/development/docker.md`
- `docs/operations/deployment.md`
