# Dependency Rules

Allowed:

- `api -> application`
- `application -> domain`
- `adapter -> application ports`
- `bootstrap -> concrete classes`

Forbidden:

- `domain -> api`
- `domain -> persistence`
- `domain -> infrastructure`
- `application -> concrete persistence`
- `application -> external vendor SDK`

## Enforcement

Each layer is a separate CMake target with only its direct dependencies exposed.
Source files use target-provided include directories instead of parent-relative
includes.

The composition target is the only target allowed to depend on concrete
adapters.
