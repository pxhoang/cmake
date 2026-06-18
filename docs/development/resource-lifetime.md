# Resource Lifetime

Linux resources are ownership-bearing objects and MUST use RAII.

## Ownership

This guide owns implementation rules for acquired operating-system resources
and deterministic cleanup. General C++ object ownership lives in
`docs/development/memory-and-ownership.md`; deployed runtime ownership and
permissions live in `docs/operations/runtime-hardening.md`.

## Must

Resources include:

1. File descriptors.
2. Files and temporary files.
3. Directory handles.
4. Locks and lock files.
5. Threads and worker handles.
6. Child processes.
7. Sockets and pipes.
8. Signal handlers and timers.
9. Memory-mapped regions.

Every acquired resource MUST have one clear owner and deterministic cleanup.
Resource acquisition and release MUST be exception-safe. Cleanup code MUST NOT
depend on callers remembering to call a manual `close`, `unlock`, `join`, or
`cleanup` function when RAII can express the same lifetime.

Temporary files and runtime state MUST be created under `.img/` for generated
project output unless they are documented runtime deployment state.

Plans that add resource ownership MUST state acquisition, cleanup, failure, and
shutdown behavior.

## Should

1. Prefer standard-library RAII types when they exist.
2. Keep resource ownership local to the smallest component that can manage
   cleanup.
3. Use small project-owned RAII wrappers for Linux resources without standard
   wrappers.

## Workflow

When adding a resource, define acquisition, ownership transfer, normal cleanup,
failure cleanup, and shutdown behavior before implementation.

## Verification

Tests or review notes MUST cover failure paths and cleanup behavior for new
resource ownership.

## Related Guides

- `docs/development/memory-and-ownership.md`
- `docs/development/thread-safety.md`
- `docs/operations/runtime-hardening.md`
