# Operations: Runtime Configuration

Runtime configuration includes deployed config files, environment variables,
example values, runtime state paths, and secret delivery.

## Rules

1. Runtime configuration examples and defaults MUST live under
   `ops/config/<app>/`.
2. Application configuration loading may live in app-level infrastructure.
3. Domain and application business rules MUST NOT read files, environment
   variables, command-line process state, or machine-local paths directly.
4. Configuration parsers MUST validate required fields and report actionable
   errors.
5. Example configuration MUST use non-secret placeholder values.
6. Secrets, credentials, private keys, tokens, production values, and personal
   machine paths MUST NOT be committed.
7. Generated runtime state belongs under `.img/runtime/`.

## Required Evidence

Plans and reviews that add or change runtime configuration MUST state:

1. Configuration path.
2. Environment variables.
3. Required fields.
4. Validation behavior.
5. Error behavior.
6. Secret delivery mechanism.
7. Generated runtime state location.
