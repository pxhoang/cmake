# Development: Linux Platform

Linux behavior is part of the design surface for service code.

## Rules

1. Service loops MUST define SIGINT and SIGTERM behavior.
2. Executable failure modes MUST return meaningful exit codes.
3. Runtime paths MUST be configurable or documented.
4. Deployment assets MUST document ownership and access needs.
5. Intervals and deadlines MUST use monotonic time.
6. Environment variables MUST be validated and malformed values reported.
7. Parsing code MUST NOT depend on unspecified locale behavior unless
   documented.
8. Low-level failures MUST preserve enough errno or system error context for
   diagnosis.

Domain and application business rules MUST NOT depend directly on Linux
process, filesystem, signal, or environment APIs.

Linux-specific behavior SHOULD stay behind adapters or app-level
infrastructure.

For signal, timer, filesystem, or process behavior, include integration or e2e
coverage when unit tests cannot prove the behavior.

## Required Evidence

Plans and reviews that add Linux API usage MUST state:

1. Affected layer.
2. Signal behavior when applicable.
3. Exit-code behavior when applicable.
4. Runtime path and permission behavior.
5. Time source for intervals and deadlines.
6. Low-level error context preserved for diagnosis.
7. Test layer used for platform behavior.
