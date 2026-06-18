# Dependency Management

Third-party dependencies increase build, security, licensing, and maintenance
risk.

## Ownership

This guide owns development-time dependency selection, justification, version
control, and review expectations. Architecture-level dependency direction
lives in `docs/architecture/dependency-rules.md`; security requirements live
in `docs/architecture/security.md`.

## Must

1. New dependencies MUST be justified in the plan.
2. Dependency purpose, layer placement, license, and transitive impact MUST be
   stated.
3. External SDKs and libraries MUST be isolated behind the correct adapter or
   library boundary.
4. Domain and application layers MUST NOT depend directly on vendor SDKs.
5. Security-sensitive dependencies require explicit risk review.

## Should

1. Versions SHOULD be pinned or controlled through existing dependency
   mechanisms.
2. Do not add a dependency for behavior that is simpler and safer to implement
   locally within existing project patterns.

## Workflow

State the dependency purpose, placement, license, transitive impact, and
version source before implementation.

## Verification

Verify that the dependency is linked only from the intended target and does not
leak into forbidden layers.

## Related Guides

- `docs/architecture/dependency-rules.md`
- `docs/architecture/security.md`
- `docs/development/cmake.md`
