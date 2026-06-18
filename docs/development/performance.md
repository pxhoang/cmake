# Performance

Performance work must be bounded, measured, and compatible with architecture.

## Ownership

This guide owns implementation-level performance practices, measurement, and
tradeoff expectations. Responsiveness placement rules live in
`docs/architecture/concurrency.md`; runtime service expectations live in
`docs/operations/service-operations.md`.

## Must

1. Polling intervals, retries, queues, and buffers MUST have explicit bounds.
2. Optimization MUST NOT bypass layer boundaries, testability, error handling,
   or security rules.

## Should

1. Prefer clear algorithms and ownership before micro-optimization.
2. State expected algorithmic complexity for non-trivial data processing.
3. Avoid unnecessary copies on hot paths, but do not sacrifice lifetime safety.
4. Avoid unbounded memory growth.
5. Blocking I/O should not be added to paths that must remain responsive.
6. Performance changes SHOULD include measurement or a clear rationale.

## Workflow

Identify the path being optimized, expected complexity, resource bounds, and
the behavior that must remain correct.

## Verification

Performance changes SHOULD include a measurement, benchmark, profile, or clear
rationale when measurement is not practical.

## Related Guides

- `docs/architecture/concurrency.md`
- `docs/development/memory-and-ownership.md`
- `docs/development/testing-guide.md`
