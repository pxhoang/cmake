# Development: Thread Safety

Threaded code MUST be designed, bounded, and testable.

## Rules

1. Detached threads are forbidden unless explicitly approved by design.
2. Thread ownership and shutdown responsibility MUST be clear.
3. Shared mutable state MUST be protected by a mutex, atomic protocol, message
   passing, or ownership confinement.
4. Lock ordering MUST be documented when more than one lock can be held.
5. Condition variables MUST use predicates.
6. Atomics MUST include a clear memory-ordering rationale when not using the
   default sequential consistency.
7. Blocking waits MUST have a shutdown path and SHOULD be wakeable, timed, or
   interruptible.
8. Thread and synchronization ownership MUST follow
   `.specify/memory/dev/resource-lifetime.md`.

Plans that add threads, timers, workers, async callbacks, polling, or shared
state MUST include the concurrency model, cancellation path, and test strategy.

Meaningful concurrency changes SHOULD run ThreadSanitizer or equivalent
analysis. If that cannot run, report the blocker and residual risk.

## Required Evidence

Plans and reviews that add or change threaded behavior MUST state:

1. Thread owner.
2. Shared mutable state, if any.
3. Synchronization mechanism.
4. Lock ordering when more than one lock can be held.
5. Cancellation path.
6. Test or sanitizer strategy.
