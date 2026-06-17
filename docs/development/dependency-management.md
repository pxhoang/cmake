# Dependency Management

Third-party dependencies increase build, security, licensing, and maintenance
risk.

## Rules

1. New dependencies MUST be justified in the plan.
2. Dependency purpose, layer placement, license, and transitive impact MUST be
   stated.
3. External SDKs and libraries MUST be isolated behind the correct adapter or
   library boundary.
4. Domain and application layers MUST NOT depend directly on vendor SDKs.
5. Versions SHOULD be pinned or controlled through existing dependency
   mechanisms.
6. Security-sensitive dependencies require explicit risk review.

Do not add a dependency for behavior that is simpler and safer to implement
locally within existing project patterns.
