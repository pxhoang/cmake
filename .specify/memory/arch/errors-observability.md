# Architecture: Errors and Observability

Errors MUST be explicit at layer boundaries. Observability belongs at
boundaries and orchestration points, not inside business rules.

## Error Rules

1. Domain and application code MUST NOT silently swallow failures from ports or
   adapters.
2. Adapter failures MUST be translated into application-visible errors without
   leaking mechanism-specific details into domain types.
3. Input MUST be validated at API, configuration, persistence, and external
   mechanism boundaries.
4. Diagnostics MUST preserve enough context for debugging without exposing
   secrets.
5. Code MUST use exceptions, result types, or status objects consistently with
   nearby code.
6. Reusable code MUST NOT use process termination, global state mutation, or
   logging as a substitute for returning an error.
7. Unexpected failures MUST NOT be converted into default success values.

Plans MUST describe error behavior for new boundary code, persistence code,
configuration parsing, and external communication surfaces.

## Observability Rules

1. User-facing command output and service logs MUST describe meaningful state
   transitions and failures.
2. Domain logic MUST NOT write to stdout, stderr, logs, files, or metrics.
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
2. The thread field MUST identify the current thread as a hexadecimal 32-bit
   value in the inclusive range `0x00000000` through `0xFFFFFFFF`.
3. The thread field MUST use the `0x` prefix and exactly 8 hexadecimal digits.
4. `cls_name::function_name()` MUST name the emitting class or component and
   function.
5. For free functions, use the nearest component name as `cls_name`.
6. `MESSAGE` MUST be uppercase words separated by `_`.
7. `MESSAGE` MUST be one logical event name, contain no spaces, and contain at
   most three words.
8. Key-value fields MUST use `name=value` pairs separated by `|`.
9. Values MUST be escaped, sanitized, or summarized so each log record remains
   one physical line.
10. Logs MUST NOT include secrets or full sensitive configuration values.

Example:

```text
[2026-06-18T10:15:30.123Z] [0x00000001] Parser::Parse() PARSE_INFO source=config|bytes=42
```

## Required Evidence

Plans and reviews that add boundary, persistence, configuration, external
communication, or service behavior MUST state:

1. Expected success signal.
2. Explicit failure cases.
3. Error type or result mechanism.
4. Safe diagnostic context.
5. Log event names and key-value fields when logs are part of the contract.
6. Test coverage for user-facing or operational diagnostics.
