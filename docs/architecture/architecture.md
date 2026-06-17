# Architecture

Projects governed by this guide use feature-oriented Clean Architecture inside
each executable application. Business rules live in inner layers. External
mechanisms live in outer layers. CMake target boundaries enforce the dependency
direction.

## Required Feature Shape

```text
src/apps/<app>/features/<feature>/
|-- domain/
|-- application/
|-- api/
`-- adapters/
    |-- console/
    `-- persistence/
```

Layer responsibilities:

1. `domain`: pure business types, invariants, and rules.
2. `application`: use cases and ports.
3. `api`: in-process input adapters for callers.
4. `adapters`: external mechanisms and side effects.
5. `bootstrap`: composition root that wires concrete implementations.

## Required Rules

Feature code MUST stay inside its feature slice. Agents MUST NOT flatten
layers, skip ports, put business rules in adapters, or wire concrete
implementations outside `bootstrap`.

Each application MUST use one shared application namespace for public
application-owned C++ types. Directory boundaries express architecture layers;
they MUST NOT be mirrored as nested C++ namespaces.

All applications and features MUST follow this structure unless the
constitution is amended.
