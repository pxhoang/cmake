# Security

Security-sensitive material MUST NOT be committed. This includes credentials,
tokens, private keys, production secrets, personal machine paths, and private
runtime state.

Rules:

1. Treat file paths, environment variables, config files, IPC messages, and
   external input as untrusted until validated.
2. Do not log secrets or full sensitive configuration values.
3. Keep permissions, ownership, systemd, package, and deployment behavior in
   `ops/` and document operational impact.
4. New external communication surfaces MUST include authentication,
   authorization, input validation, timeout, and failure-mode considerations in
   the plan.
5. Dependency additions MUST be explicit, justified, and isolated behind the
   correct layer or library boundary.
6. Test fixtures MUST use non-secret sample data.

Security shortcuts, temporary plaintext secrets, and local-only assumptions are
non-compliant unless explicitly approved by constitutional amendment.
