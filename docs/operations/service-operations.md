# Service Operations

Operational assets belong under `ops/`:

```text
ops/config/   Runtime configuration examples and defaults
ops/deploy/   Service managers, package metadata, and deployment assets
```

Long-running services MUST define shutdown behavior for SIGINT and SIGTERM.
Retry, polling, and reconciliation loops MUST have explicit stop conditions and
observable failure behavior.

Service logs and command output should describe meaningful state transitions
and failures without exposing secrets. Project-owned service logs MUST follow
the format in `docs/architecture/observability.md`.

Changes to systemd units, package metadata, runtime configuration, or service
operation behavior MUST update `docs/operations/`.
