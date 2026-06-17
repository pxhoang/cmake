# Runtime Hardening

Runtime hardening is required for deployable services.

## Rules

1. Services SHOULD run with the least privileges practical.
2. Runtime state directories MUST be explicit and documented.
3. Package and service-manager assets MUST document ownership and permissions.
4. Secrets MUST be supplied through approved runtime mechanisms, not committed
   files.
5. Services MUST define shutdown behavior.
6. Logs MUST not expose secrets.
7. External communication surfaces MUST define authentication, authorization,
   validation, timeout, and failure behavior.

When systemd is used, service units SHOULD consider hardening options such as
restricted writable paths, private temporary directories, and explicit state
directories where compatible with the service.
