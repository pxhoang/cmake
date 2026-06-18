# Operations: Deployment

Deployment assets belong under `ops/deploy/`. Runtime configuration examples
and defaults belong under `ops/config/`.

## Required Deployment Details

Application-specific deployment work MUST document:

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

Deployment examples and generated deployment artifacts MUST NOT weaken this
memory.

## Required Evidence

Plans and reviews that add or change deployment behavior MUST state:

1. Service entry point.
2. Runtime mode.
3. Shutdown behavior.
4. Configuration inputs.
5. State directories.
6. Permissions and ownership.
7. Package output path.
8. Rollback or cleanup behavior when relevant.
