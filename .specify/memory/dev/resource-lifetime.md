# Development: Resource Lifetime

Linux resources are ownership-bearing objects and MUST use RAII.

## Resource Types

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

## Rules

Every acquired resource MUST have one clear owner and deterministic cleanup.

Resource acquisition and release MUST be exception-safe. Cleanup code MUST NOT
depend on callers remembering to call a manual `close`, `unlock`, `join`, or
`cleanup` function when RAII can express the same lifetime.

Temporary files and runtime state MUST be created under `.img/` for generated
project output unless they are documented runtime deployment state.

Plans that add resource ownership MUST state acquisition, cleanup, failure, and
shutdown behavior.

Tests or review notes MUST cover failure paths and cleanup behavior for new
resource ownership.

## Required Evidence

Plans and reviews that add operating-system resource ownership MUST state:

1. Resource type.
2. Acquisition point.
3. Owner.
4. Normal cleanup path.
5. Failure cleanup path.
6. Shutdown behavior.
7. Test or review evidence for cleanup.
