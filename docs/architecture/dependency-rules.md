# Dependency Rules

Dependencies MUST point inward. Inner layers own policy. Outer layers own
mechanisms.

## Allowed Dependencies

```text
api -> application
application -> domain
adapters -> application ports
adapters/persistence -> application ports
bootstrap -> concrete outer layers
```

## Forbidden Dependencies

```text
domain -> api
domain -> adapters
domain -> infrastructure
domain -> vendor SDKs
application -> concrete adapter implementations
application -> external vendor SDKs
api -> concrete adapter implementations
api -> persistence implementations
```

## Enforcement

Each layer MUST be a separate CMake target with only its direct dependencies
exposed. Source files MUST use target-provided include directories instead of
parent-relative includes.

The composition target is the only target allowed to depend on concrete
adapters, including persistence implementations.

Ports live in `application`. Implementations live in `adapters/`, including
persistence implementations under `adapters/persistence/`.

Application behavior tests MUST use fakes for ports and MUST NOT link concrete
adapter implementations.

## Feature Template

New features MUST follow this shape unless the constitution is amended:

```text
features/<feature>/
|-- domain/
|-- application/
|-- api/
`-- adapters/
    |-- console/
    `-- persistence/
```

Directory boundaries are architectural boundaries. Public application-owned C++
types use one shared application namespace; layer folders MUST NOT be mirrored
as nested C++ namespaces.
