# Responsiveness and Concurrency

This guide owns architectural concurrency placement and responsiveness
requirements. Implementation-level thread-safety rules for mutexes, atomics,
condition variables, locks, and sanitizer expectations live in
`docs/development/thread-safety.md`.

Long-running applications MUST remain responsive to shutdown signals and
operational failure. For service-style code, SIGINT and SIGTERM handling MUST
be considered in the plan when loops, waits, worker threads, or blocking I/O
are introduced.

Concurrency rules:

1. Domain types MUST remain pure and free of thread, sleep, timer, file,
   process, socket, and environment dependencies.
2. Application services MUST not create detached threads or unbounded
   background work.
3. Blocking I/O belongs in adapters or app-level infrastructure and MUST have
   bounded behavior and a documented shutdown path.
4. Shared mutable state MUST be protected by clear ownership, synchronization,
   or confinement.
5. Retry, polling, and reconciliation loops MUST have explicit stop conditions
   and test coverage for failure or shutdown behavior.
6. Service loops MUST use wakeable, timed, or interruptible waits. They MUST NOT
   rely on uninterruptible sleeps for shutdown responsiveness.
7. Concurrency primitives MUST NOT appear in domain code or public
   domain/application contracts unless the primitive is the actual abstraction
   being modeled.

Concurrency primitives are allowed only where they are part of the mechanism or
orchestration being implemented. They MUST NOT be used to bypass architecture
boundaries.
