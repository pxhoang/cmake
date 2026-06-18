# Linux Platform

Linux behavior is part of the design surface for service code.

## Ownership

This guide owns implementation-level Linux API considerations. Architecture
placement rules live in `docs/architecture/concurrency.md` and
`docs/architecture/persistence-and-config.md`; deployed runtime behavior lives
in `docs/operations/`.

## Must

1. Signals: service loops MUST define SIGINT and SIGTERM behavior.
2. Exit codes: executable failure modes MUST return meaningful exit codes.
3. Filesystem paths: runtime paths MUST be configurable or documented.
4. Permissions: deployment assets MUST document ownership and access needs.
5. Time: use monotonic time for intervals and deadlines.
6. Environment variables: validate and report missing or malformed values.
7. Locale and encoding: parsing code MUST not depend on unspecified locale
   behavior unless documented.
8. POSIX errors: preserve enough errno/system error context for diagnosis.

Domain and application business rules MUST NOT depend directly on Linux
process, filesystem, signal, or environment APIs.

## Should

1. Prefer monotonic time for intervals and deadlines.
2. Preserve `errno` or `std::system_error` context for low-level failures.
3. Keep Linux-specific behavior behind adapters or app-level infrastructure.

## Workflow

When adding Linux API usage, state the affected layer, error behavior,
shutdown behavior, and operational impact before implementation.

## Verification

Run tests that exercise success and failure paths where practical. For signal,
timer, filesystem, or process behavior, include integration or e2e coverage
when unit tests cannot prove the behavior.

## Related Guides

- `docs/architecture/concurrency.md`
- `docs/architecture/persistence-and-config.md`
- `docs/operations/service-operations.md`
- `docs/operations/deployment.md`
