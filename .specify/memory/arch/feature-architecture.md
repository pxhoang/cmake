# Architecture: Feature Architecture

Projects governed by this memory use feature-oriented Clean Architecture
inside each executable application. Business rules live in inner layers.
External mechanisms live in outer layers.

## Required Feature Shape

Every feature inside an executable application MUST use this shape unless the
constitution is amended:

```text
src/apps/<app>/features/<feature>/
|-- domain/
|-- application/
|   |-- ports/
|   `-- services/
|-- api/
`-- adapters/
    |-- console/
    `-- persistence/
```

## Layer Responsibilities

1. `domain`: pure business types, invariants, and rules.
2. `application/ports`: application-owned contracts for side effects.
3. `application/services`: workflow policy and application services.
4. `api`: in-process input adapters for callers.
5. `adapters`: external mechanisms and side effects.
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
6. Why any missing standard layer is not affected.
