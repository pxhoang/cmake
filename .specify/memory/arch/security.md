# Architecture: Security

Security-sensitive material MUST NOT be committed. This includes credentials,
tokens, private keys, production secrets, personal machine paths, and private
runtime state.

## Rules

1. File paths, environment variables, config files, IPC messages, and external
   input MUST be treated as untrusted until validated.
2. Secrets or full sensitive configuration values MUST NOT be logged.
3. Permissions, ownership, systemd, package, and deployment behavior belong in
   `ops/` assets and `.specify/memory/ops/`.
4. New external communication surfaces MUST include authentication,
   authorization, input validation, timeout, and failure-mode considerations in
   the plan.
5. Dependency additions MUST be explicit, justified, and isolated behind the
   correct layer or library boundary.
6. Test fixtures MUST use non-secret sample data.

Security shortcuts, temporary plaintext secrets, and local-only assumptions are
non-compliant unless explicitly approved by constitutional amendment.

## Required Evidence

Plans and reviews that add external input, dependency, configuration,
persistence, IPC, or deployment behavior MUST state:

1. Untrusted inputs.
2. Validation boundary.
3. Secret handling.
4. Authentication and authorization behavior for external surfaces.
5. Timeout and failure-mode behavior for external surfaces.
6. Dependency isolation and risk review when dependencies are added.
