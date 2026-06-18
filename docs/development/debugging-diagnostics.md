# Debugging and Diagnostics

Debugging support must be designed before failures happen.

## Ownership

This guide owns implementation practices for diagnostics, release-debuggability,
and failure investigation. Architecture-level observability rules and log
format live in `docs/architecture/observability.md`; deployed log handling
lives in `docs/operations/service-operations.md`.

## Must

1. Logs and command output MUST include enough context to diagnose failures.
2. Diagnostics MUST NOT expose secrets.
3. Plans that affect startup, config loading, persistence, deployment, or
   service loops MUST state how failures will be diagnosed.

## Should

1. Release builds SHOULD preserve usable debug-symbol workflows.
2. Error messages should identify the failed operation and relevant safe
   context.
3. Reproducible failures should include command, config example, and expected
   output where practical.
4. Tests should assert contractual diagnostics when diagnostics are user-facing.

## Workflow

Design diagnostic context with the failure path. Prefer explicit safe values,
operation names, paths that are safe to reveal, and actionable error text.

## Verification

When diagnostics are user-facing or operationally significant, tests SHOULD
assert the stable diagnostic contract.

## Related Guides

- `docs/architecture/observability.md`
- `docs/architecture/error-handling.md`
- `docs/operations/service-operations.md`
