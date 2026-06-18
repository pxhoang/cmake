# Architecture: Dependency Direction

Dependencies MUST point inward. Inner layers own policy. Outer layers own
mechanisms.

## Allowed Dependencies

These direct dependencies are allowed only when the corresponding layer or
mechanism exists for the feature:

```text
api -> application/services
application/services -> application/ports
application/ports -> domain
adapters/<mechanism> -> application/ports
adapters/persistence -> application/ports
bootstrap -> concrete outer layers
```

## Forbidden Dependencies

```text
domain -> api
domain -> adapters
domain -> infrastructure
domain -> vendor SDKs
application/ports -> concrete adapter implementations
application/services -> concrete adapter implementations
application -> external vendor SDKs
api -> concrete adapter implementations
api -> persistence implementations
```

## Enforcement

Each layer MUST be a separate CMake target with only its direct dependencies
exposed.

Source files MUST use target-provided include directories instead of
parent-relative includes.

The composition target is the only target allowed to depend on concrete
adapters, including persistence implementations.

Ports live in `application/ports`. Application services live in
`application/services`. Concrete mechanism implementations live in
mechanism-specific `adapters/` directories when the feature introduces those
mechanisms. Persistence implementations live under `adapters/persistence/`
when persistence is required.

Application behavior tests MUST use fakes for ports and MUST NOT link concrete
adapter implementations.

## Required Evidence

Plans and reviews that add or change dependencies MUST state:

1. Intended target graph.
2. Direct dependency added to each target.
3. Concrete adapter dependencies and the composition target that owns them.
4. Fake or test-double strategy for application behavior tests.
5. Any forbidden dependency that was considered and rejected.
