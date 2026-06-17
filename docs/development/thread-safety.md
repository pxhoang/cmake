# Thread Safety

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
7. Blocking waits MUST have a shutdown path.
8. Domain logic MUST not create threads, sleep, or wait on synchronization.

Plans that add threads, timers, workers, async callbacks, polling, or shared
state MUST include the concurrency model, cancellation path, and test strategy.

ThreadSanitizer or equivalent analysis SHOULD be considered for meaningful
concurrency changes.
