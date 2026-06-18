# Testing Guide

Behavioral changes MUST include tests at the lowest layer that can prove the
behavior.

## Ownership

This guide owns test placement, test layer selection, and verification command
expectations. CMake test registration lives in `docs/development/cmake.md`;
review completion lives in `docs/development/code-review-checklist.md`.

## Must

1. Behavioral changes MUST include tests at the lowest layer that can prove the
   behavior.
2. Application service tests use fakes for ports and MUST NOT link concrete
   adapter implementations.
3. For shared architecture, CMake, target wiring, or cross-component behavior,
   run the full verification command unless blocked.

## Should

1. Prefer focused unit tests for pure behavior.
2. Use integration tests for bootstrap, persistence, and cross-component
   wiring.
3. Use end-to-end tests when executable, user-visible, or deployment behavior
   changes.

## Workflow

### Placement

```text
src/apps/<app>/tests/unit/       App-owned unit tests
tests/integration/<app>/         Cross-component integration tests
tests/e2e/<app>/                 End-to-end executable or deployed-flow tests
```

### Layer Rules

Domain tests cover pure business rules and value invariants.

Application service tests use fakes for ports and MUST NOT link concrete
adapter implementations.

API tests verify input translation and result mapping without depending on
concrete persistence or device adapters.

Adapter tests verify mechanism behavior without moving business rules into
adapters.

Bootstrap, persistence, and cross-component wiring belong in integration
tests. Executable flows belong in end-to-end tests when user-visible behavior
or deployment behavior changes.

## Verification

The preferred full verification command is:

```bash
./tooling/scripts/test.sh
```

For shared architecture, CMake, target wiring, or cross-component behavior,
run the full verification command unless blocked. If verification cannot run,
report the exact command, failure reason, and residual risk.

## Related Guides

- `docs/development/cmake.md`
- `docs/development/code-review-checklist.md`
- `docs/development/static-analysis.md`
