# Thread Safety

Threaded code MUST be designed, bounded, and testable.

## Ownership

Architecture-level placement and service responsiveness rules live in
`docs/architecture/concurrency.md`. This guide owns implementation rules for
threads, locks, atomics, waits, and verification.

## Must

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
   `docs/development/resource-lifetime.md`.

## Should

1. Prefer ownership confinement or message passing over shared mutable state.
2. Keep synchronization close to the state it protects.
3. ThreadSanitizer or equivalent analysis SHOULD be considered for meaningful
   concurrency changes.

## Workflow

Plans that add threads, timers, workers, async callbacks, polling, or shared
state MUST include the concurrency model, cancellation path, and test strategy.

## Verification

Meaningful concurrency changes SHOULD run ThreadSanitizer or equivalent
analysis. If that cannot run, report the blocker and residual risk.

## Related Guides

- `docs/architecture/concurrency.md`
- `docs/development/resource-lifetime.md`
- `docs/development/static-analysis.md`
