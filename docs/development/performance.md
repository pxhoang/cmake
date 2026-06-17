# Performance

Performance work must be bounded, measured, and compatible with architecture.

## Rules

1. Prefer clear algorithms and ownership before micro-optimization.
2. State expected algorithmic complexity for non-trivial data processing.
3. Avoid unnecessary copies on hot paths, but do not sacrifice lifetime safety.
4. Avoid unbounded memory growth.
5. Polling intervals, retries, queues, and buffers MUST have explicit bounds.
6. Blocking I/O should not be added to paths that must remain responsive.
7. Performance changes SHOULD include measurement or a clear rationale.

Optimization MUST NOT bypass layer boundaries, testability, error handling, or
security rules.
