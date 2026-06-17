# Persistence and Configuration

Persistence ports MUST be owned by the `application` layer. Persistence
implementations MUST live under `adapters/persistence/`. Persistence code MUST
not introduce business rules that belong in domain or application use cases.

Configuration rules:

1. Runtime configuration examples and defaults MUST live under `ops/config/`.
2. Deployment configuration MUST live under `ops/deploy/`.
3. Application configuration loading may live in app-level infrastructure.
4. Domain and application layers MUST NOT read files, environment variables, or
   process state directly.
5. Configuration parsing MUST validate required fields and report actionable
   errors.
6. Secrets, credentials, private keys, tokens, and machine-local paths MUST NOT
   be committed.

Generated runtime state, test output, package output, downloaded dependencies,
and build output MUST stay under `.img/`.
