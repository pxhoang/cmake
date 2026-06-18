# Architecture: Feature Architecture

Projects governed by this memory use feature-oriented Clean Architecture
inside each executable application. Business rules live in inner layers.
External mechanisms live in outer layers.

## Required Feature Shape

Every feature inside an executable application MUST use this inner-layer shape
unless the constitution is amended:

```text
src/apps/<app>/features/<feature>/
|-- domain/
|-- application/
|   |-- ports/
|   `-- services/
|-- api/                 # when the feature exposes an in-process API boundary
`-- adapters/            # when the feature introduces concrete mechanisms
    `-- <mechanism>/     # only the mechanisms required by the feature
```

Adapter subdirectories MUST be mechanism-driven. A feature MUST NOT add any
concrete adapter directory unless the feature explicitly introduces that
mechanism.

When persistence is required, concrete persistence implementations MUST live
under `adapters/persistence/` as specified by `persistence-config.md`.

## Layer Responsibilities

1. `domain`: pure business types, invariants, and rules.
2. `application/ports`: application-owned contracts for side effects.
3. `application/services`: workflow policy and application services.
4. `api`: in-process input adapters for callers when the feature exposes one.
5. `adapters`: external mechanisms and side effects when required.
6. `bootstrap`: composition root that wires concrete implementations.

## Required Rules

Feature code MUST stay inside its feature slice.

Agents MUST NOT:

1. Flatten layers.
2. Skip ports for side effects.
3. Put business rules in adapters, APIs, handlers, or bootstrap.
4. Wire concrete implementations outside `bootstrap` or composition targets.

Each application MUST use one shared application namespace for public
application-owned C++ types. Directory boundaries express architecture layers;
they MUST NOT be mirrored as nested C++ namespaces.

## Required Evidence

Plans and reviews that add or change feature code MUST state:

1. Application name.
2. Feature name.
3. Affected layers.
4. Public application namespace.
5. Composition root or bootstrap location.
6. Why any optional API or adapter mechanism is present or absent.
