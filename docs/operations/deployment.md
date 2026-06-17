# Deployment

Deployment assets belong under `ops/deploy/`. Runtime configuration examples
and defaults belong under `ops/config/`.

Application-specific deployment details MUST document:

1. Service entry point and runtime mode.
2. Shutdown behavior for SIGINT and SIGTERM.
3. Runtime configuration files and environment variables.
4. State directories and generated runtime files.
5. Required permissions, ownership, and service-manager settings.
6. Packaging command and package output location.
7. Operational rollback or cleanup considerations when relevant.

Generated package output MUST be created under:

```text
.img/package/
```

Generated runtime output MUST be created under:

```text
.img/runtime/
```

Application-specific deployment examples MAY live in `docs/operations/` when
they describe real deployed behavior, but they MUST NOT weaken the generic
deployment rules above.
