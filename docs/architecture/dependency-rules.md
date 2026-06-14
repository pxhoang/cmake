# Dependency Rules

Allowed:

- `api -> application`
- `application -> domain`
- `persistence -> application interfaces`
- `persistence -> domain`
- `bootstrap -> concrete classes`

Forbidden:

- `domain -> api`
- `domain -> persistence`
- `domain -> infrastructure`
- `application -> concrete persistence`
- `application -> external vendor SDK`
