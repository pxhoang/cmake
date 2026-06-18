# Static Analysis and Sanitizers

Static analysis and sanitizers are part of quality enforcement.

## Ownership

This guide owns compiler warnings, static analysis, sanitizer expectations, and
suppression rules. Test-layer selection lives in
`docs/development/testing-guide.md`; CI and tooling entry points live in
`docs/development/build-tooling-packaging.md`.

## Must

1. Compiler warnings MUST remain enabled.
2. Warning suppressions MUST be narrow and justified.
3. Suppressions MUST include a reason and the smallest practical scope.
4. Broad project-wide suppressions are not allowed without explicit approval.
5. Plans that cannot run relevant analysis MUST report the command, blocker,
   and residual risk.

## Should

1. `clang-tidy` findings SHOULD be fixed unless the finding is documented as
   not applicable.
2. AddressSanitizer and UndefinedBehaviorSanitizer SHOULD be run for memory,
   ownership, parser, container, or low-level changes.
3. ThreadSanitizer SHOULD be considered for concurrency changes.
4. Leak checks SHOULD be considered for long-running service changes.

## Workflow

Use existing scripts and CMake presets for analysis and sanitizer runs. Keep
new suppressions narrow and near the reason for the suppression.

## Verification

Report the exact analysis or sanitizer command run. If the command cannot run,
report the blocker and residual risk.

## Related Guides

- `docs/development/testing-guide.md`
- `docs/development/build-tooling-packaging.md`
- `docs/development/thread-safety.md`
