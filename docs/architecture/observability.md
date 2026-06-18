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

## Log Format

Project-owned service logs MUST be single-line records with this field order:

```text
[timestamp] [0x00000000-0xFFFFFFFF] cls_name::function_name() MESSAGE var1=value1|var2=value2|...
```

Rules:

1. `timestamp` MUST be an ISO-8601 timestamp with timezone information.
2. The second field MUST identify the current thread as a hexadecimal 32-bit
   value in the inclusive range `0x00000000` through `0xFFFFFFFF`. It MUST use
   the `0x` prefix and exactly 8 hexadecimal digits.
3. `cls_name::function_name()` MUST name the class or component and function
   that emits the log. For free functions, use the nearest component name as
   `cls_name`.
4. `MESSAGE` MUST be uppercase words separated by `_`.
5. `MESSAGE` MUST be one logical event name, contain no spaces, and contain at
   most three words.
6. Key-value fields MUST use `name=value` pairs separated by `|`.
7. Values MUST be escaped, sanitized, or summarized so each log record remains
   one physical line.
8. Logs MUST NOT include secrets or full sensitive configuration values.

Examples:

```text
[2026-06-18T10:15:30.123Z] [0x00000001] Parser::Parse() PARSE_INFO source=config|bytes=42
[2026-06-18T10:15:30.124Z] [0x00000001] Parser::Parse() PARSE_ERR source=config|reason=invalid_format
```

Plans that add service mode, background work, external communication, or
persistence behavior MUST state what will be observable when the operation
succeeds, fails, or shuts down.
