# Architecture: Persistence and Configuration

Persistence ports MUST be owned by the `application` layer. Persistence
implementations MUST live under `adapters/persistence/`.

Persistence code MUST NOT introduce business rules that belong in domain or
application services.

## Configuration Rules

1. Runtime configuration is an operational concern.
2. Concrete runtime configuration files, environment variables, examples,
   deployment values, and secret delivery rules are owned by operations memory.
3. Application configuration loading may live in app-level infrastructure.
4. Domain and application layers MUST NOT read files, environment variables, or
   process state directly.
5. Configuration parsing MUST validate required fields and report actionable
   errors.
6. Secrets, credentials, private keys, tokens, and machine-local paths MUST NOT
   be committed.

Generated runtime state, test output, package output, downloaded dependencies,
and build output MUST stay under `.img/`.

## Required Evidence

Plans and reviews that add persistence or configuration behavior MUST state:

1. Application-owned port name.
2. Concrete adapter path.
3. Configuration loader location.
4. Required fields and validation behavior.
5. Error behavior for missing, malformed, or inaccessible configuration.
6. Secret handling and generated state location.
