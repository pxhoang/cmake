# Debugging and Diagnostics

Debugging support must be designed before failures happen.

## Rules

1. Release builds SHOULD preserve usable debug-symbol workflows.
2. Logs and command output MUST include enough context to diagnose failures.
3. Diagnostics MUST NOT expose secrets.
4. Error messages should identify the failed operation and relevant safe
   context.
5. Reproducible failures should include command, config example, and expected
   output where practical.
6. Tests should assert contractual diagnostics when diagnostics are user-facing.

Plans that affect startup, config loading, persistence, deployment, or service
loops MUST state how failures will be diagnosed.
