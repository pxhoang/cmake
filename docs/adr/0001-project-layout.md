# ADR 0001: Project Layout

## Decision

- `bin/` contains executable applications.
- `lib/` contains internal reusable libraries.
- `external/` contains dependency metadata only.
- `.img/` contains generated/downloaded/build/package output.

## Reason

This keeps the repository clean and scalable for many binaries and libraries.
