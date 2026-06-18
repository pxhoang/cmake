# Development: Dependencies and Performance

Third-party dependencies increase build, security, licensing, and maintenance
risk. Performance work must be bounded, measured, and compatible with
architecture.

## Dependency Rules

1. New dependencies MUST be justified in the plan.
2. Dependency purpose, layer placement, license, and transitive impact MUST be
   stated.
3. External SDKs and libraries MUST be isolated behind the correct adapter or
   library boundary.
4. Domain and application layers MUST NOT depend directly on vendor SDKs.
5. Security-sensitive dependencies require explicit risk review.
6. Versions SHOULD be pinned or controlled through existing dependency
   mechanisms.

Dependencies MUST NOT be added for behavior that is simpler and safer to
implement locally within existing project patterns.

Verify that the dependency is linked only from the intended target and does not
leak into forbidden layers.

## Performance Rules

1. Polling intervals, retries, queues, and buffers MUST have explicit bounds.
2. Optimization MUST NOT bypass layer boundaries, testability, error handling,
   or security rules.
3. Non-trivial data processing SHOULD state expected algorithmic complexity.
4. Performance changes SHOULD include measurement, benchmark, profile, or
   clear rationale when measurement is not practical.

Unbounded memory growth MUST NOT be introduced. Blocking I/O MUST NOT be added
to paths that must remain responsive.

## Required Evidence

Plans and reviews that add dependencies or performance-sensitive behavior MUST
state:

1. Dependency purpose, version source, license, and transitive impact.
2. Target and layer that own the dependency.
3. Isolation boundary for external SDKs or libraries.
4. Security risk review when applicable.
5. Bounds for polling, retries, queues, buffers, and memory growth.
6. Measurement, benchmark, profile, or rationale for performance changes.
