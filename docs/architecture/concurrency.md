# Responsiveness and Concurrency

Long-running applications MUST remain responsive to shutdown signals and
operational failure. For service-style code, SIGINT and SIGTERM handling MUST
be considered in the plan when loops, waits, worker threads, or blocking I/O
are introduced.

Concurrency rules:

1. Domain types MUST remain pure and free of thread, sleep, timer, file,
   process, socket, and environment dependencies.
2. Application use cases MUST not create detached threads or unbounded
   background work.
3. Blocking I/O belongs in adapters or app-level infrastructure and MUST have a
   bounded behavior or documented shutdown path.
4. Shared mutable state MUST be protected by clear ownership, synchronization,
   or confinement.
5. Retry, polling, and reconciliation loops MUST have explicit stop conditions
   and test coverage for failure or shutdown behavior.

Concurrency primitives are allowed only where they are part of the mechanism or
orchestration being implemented. They MUST NOT be used to bypass architecture
boundaries.
