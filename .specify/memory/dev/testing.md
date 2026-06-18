# Development: Testing

Behavioral changes MUST include tests at the lowest layer that can prove the
behavior.

## Placement

```text
src/apps/<app>/tests/unit/       App-owned unit tests
tests/integration/<app>/         Cross-component integration tests
tests/e2e/<app>/                 End-to-end executable or deployed-flow tests
```

Every application MUST have all three test layers:

1. Unit tests (in `src/apps/<app>/tests/unit/`)
2. Integration tests (in `tests/integration/<app>/`)
3. End-to-end tests (in `tests/e2e/<app>/`)

## Layer Rules

1. Domain tests cover pure business rules and value invariants.
2. Application service tests use fakes for ports and MUST NOT link concrete
   adapter implementations.
3. API tests verify input translation and result mapping without depending on
   concrete persistence or device adapters.
4. Adapter tests verify mechanism behavior without moving business rules into
   adapters.
5. Bootstrap, persistence, and cross-component wiring belong in integration
   tests.
6. Executable flows belong in end-to-end tests when user-visible behavior or
   deployment behavior changes.

## Verification Command

The preferred full verification command is:

```bash
./tooling/scripts/test.sh
```

For shared architecture, CMake, target wiring, or cross-component behavior,
run the full verification command unless blocked.

If verification cannot run, report the exact command, failure reason, and
residual risk.

## Required Evidence

Plans and reviews that affect behavior MUST state:

1. Test layer selected.
2. Test path.
3. Behavior proven by the test.
4. Fakes or test doubles used for ports.
5. Verification command.
6. Rationale when a behavioral change has no test.
