# Dependency Rules

Allowed:

- `api -> application`
- `application -> domain`
- `adapters -> application ports`
- `persistence -> application ports`
- `bootstrap -> concrete classes`

Forbidden:

- `domain -> api`
- `domain -> persistence`
- `domain -> infrastructure`
- `application -> concrete persistence`
- `application -> concrete adapters`
- `application -> external vendor SDK`
- `api -> concrete adapters`
- `api -> persistence`

## Enforcement

Each layer is a separate CMake target with only its direct dependencies exposed.
Source files use target-provided include directories instead of parent-relative
includes.

The composition target is the only target allowed to depend on concrete
adapters or persistence implementations.

## Feature Template

New features should follow this shape unless there is a concrete reason not to:

```text
features/<feature>/
├── domain/
├── application/
├── api/
├── adapters/
└── persistence/
```

Ports live in `application`. Implementations live in `adapters/` or
`persistence/`. Tests for application behavior should use fakes and should not
link concrete persistence or external adapters.
