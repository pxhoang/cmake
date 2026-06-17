# Observability

Observability belongs at boundaries and orchestration points, not inside
business rules.

Rules:

1. User-facing command output and service logs MUST describe meaningful state
   transitions and failures.
2. Domain logic MUST not write to stdout, stderr, logs, files, or metrics.
3. Observability mechanisms belong in API, adapters, bootstrap, or app-level
   infrastructure.
4. Logs and diagnostics MUST preserve debugging context without exposing
   secrets.
5. Tests that depend on output MUST assert stable behavior, not incidental
   formatting unless formatting is the contract.

Plans that add service mode, background work, external communication, or
persistence behavior MUST state what will be observable when the operation
succeeds, fails, or shuts down.
