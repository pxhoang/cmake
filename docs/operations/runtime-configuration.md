# Runtime Configuration

Runtime configuration examples and defaults belong under:

```text
ops/config/<app>/
```

Application configuration loading may live in app-level infrastructure.
Domain and application business rules MUST NOT read files, environment
variables, command-line process state, or machine-local paths directly.

Configuration parsers MUST validate required fields and report actionable
errors. Example configuration MUST use non-secret placeholder values.

Secrets, credentials, private keys, tokens, production values, and personal
machine paths MUST NOT be committed.

Generated runtime state belongs under `.img/runtime/`.
