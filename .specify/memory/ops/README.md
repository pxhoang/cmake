# Operations Memory

This section owns binding operational rules for deployment, runtime
configuration, service operation, and runtime hardening.

## Rule Files

Read the focused file for the affected operations topic:

1. `deployment.md`
2. `runtime-configuration.md`
3. `service-operations.md`
4. `runtime-hardening.md`

## Section Gates

Operations work MUST satisfy:

1. Operational assets live under `ops/`.
2. Deployment assets live under `ops/deploy/`.
3. Runtime configuration examples and defaults live under `ops/config/<app>/`.
4. Services define shutdown, runtime state, permissions, and rollback behavior
   when relevant.
5. Runtime configuration validates required fields and never commits secrets.
6. Long-running services expose meaningful, secret-safe operational state.
7. Runtime hardening is considered for deployable services.

## Required Evidence

Operations plans and reviews MUST cite the focused operations memory file that
owns each affected rule and provide the evidence required by that file.
