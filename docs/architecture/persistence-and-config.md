# Persistence and Configuration

Persistence ports MUST be owned by the `application` layer. Persistence
implementations MUST live under `adapters/persistence/`. Persistence code MUST
not introduce business rules that belong in domain or application services.

Configuration rules:

1. Runtime configuration is an operational concern. Concrete runtime
   configuration files, environment variables, examples, deployment values, and
   secret delivery rules are owned by `docs/operations/runtime-configuration.md`.
2. Application configuration loading may live in app-level infrastructure.
3. Domain and application layers MUST NOT read files, environment variables, or
   process state directly.
4. Configuration parsing MUST validate required fields and report actionable
   errors.
5. Secrets, credentials, private keys, tokens, and machine-local paths MUST NOT
   be committed.

Generated runtime state, test output, package output, downloaded dependencies,
and build output MUST stay under `.img/`. Runtime/deployment output locations
are specified by `docs/operations/deployment.md`.
