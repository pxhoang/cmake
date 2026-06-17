# Dependency Rules

Allowed:

- `api -> application`
- `application -> domain`
- `adapters -> application ports`
- `adapters/persistence -> application ports`
- `bootstrap -> concrete classes`

Forbidden:

- `domain -> api`
- `domain -> adapters`
- `domain -> infrastructure`
- `application -> concrete adapter implementations`
- `application -> external vendor SDK`
- `api -> concrete adapter implementations`

## Enforcement

Each layer is a separate CMake target with only its direct dependencies exposed.
Source files use target-provided include directories instead of parent-relative
includes.

The composition target is the only target allowed to depend on concrete
adapters, including persistence implementations.

## Feature Template

New features should follow this shape unless there is a concrete reason not to:

```text
features/<feature>/
├── domain/
├── application/
├── api/
└── adapters/
    ├── console/
    └── persistence/
```

Ports live in `application`. Implementations live in `adapters/`, including
persistence implementations under `adapters/persistence/`. Tests for
application behavior should use fakes and should not link concrete adapter
implementations.
