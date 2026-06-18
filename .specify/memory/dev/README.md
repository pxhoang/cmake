# Development Memory

This section owns binding development rules for C++ style, build tooling,
tests, ownership, resource lifetime, thread safety, Linux behavior, static
analysis, dependencies, performance, local workflow, and review completion.

## Rule Files

Read the focused file for the affected development topic:

1. `cpp-style.md`
2. `cmake-build.md`
3. `testing.md`
4. `memory-ownership.md`
5. `resource-lifetime.md`
6. `thread-safety.md`
7. `linux-platform.md`
8. `static-analysis.md`
9. `dependencies-performance.md`
10. `local-workflow.md`
11. `review-workflow.md`

## Section Gates

Development work MUST satisfy:

1. Project-owned C++ follows Google C++ Style plus project memory.
2. Behavior changes include tests at the lowest sufficient layer.
3. Build, package, Docker, local, and CI entry points remain reproducible.
4. Ownership and cleanup are explicit.
5. Threads, waits, timers, and shared state are bounded and testable.
6. Linux runtime behavior is designed deliberately.
7. Static analysis, sanitizers, or residual risk are reported.
8. Dependency and performance tradeoffs are explicit.
9. Reviews check constitutional gates before work is considered done.

## Required Evidence

Development plans and reviews MUST cite the focused development memory file
that owns each affected rule and provide the evidence required by that file.
