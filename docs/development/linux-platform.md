# Linux Platform

Linux behavior is part of the design surface for service code.

## Required Considerations

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
