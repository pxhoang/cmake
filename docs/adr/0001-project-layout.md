# ADR 0001: Project Layout

## Decision

- `src/apps/` contains executable applications.
- `src/libs/` contains internal reusable libraries.
- `tests/` contains cross-component integration and end-to-end tests.
- `tooling/` contains CMake modules, scripts, Docker, and dependencies.
- `ops/` contains runtime configuration and deployment assets.
- `docs/` contains ADR, architecture, development, operations, and Spec Kit
  guidance.
- `.img/` contains generated/downloaded/build/package output.

## Reason

This separates product code, engineering tooling, operational assets, and
generated output while keeping target-specific `CMakeLists.txt` files beside
their source code.
