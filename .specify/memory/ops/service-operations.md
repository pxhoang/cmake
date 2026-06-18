# Operations: Service Operations

Operational assets belong under `ops/`:

```text
ops/config/   Runtime configuration examples and defaults
ops/deploy/   Service managers, package metadata, and deployment assets
```

## Rules

1. Long-running services MUST define shutdown behavior for SIGINT and SIGTERM.
2. Retry, polling, and reconciliation loops MUST have explicit stop conditions.
3. Retry, polling, and reconciliation loops MUST have observable failure
   behavior.
4. Service logs and command output SHOULD describe meaningful state
   transitions and failures without exposing secrets.
5. Project-owned service logs MUST follow
   `.specify/memory/arch/errors-observability.md`.
6. Changes to systemd units, package metadata, runtime configuration, or
   service operation behavior MUST update affected ops assets.

## Required Evidence

Plans and reviews that add or change long-running service behavior MUST state:

1. Shutdown signal handling.
2. Stop conditions for loops.
3. Observable success and failure behavior.
4. Log event names and safe fields.
5. Affected ops assets.
