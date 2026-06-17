# Error Handling

Errors MUST be explicit at layer boundaries. Domain and application code MUST
not silently swallow failures from ports or adapters. Adapter failures MUST be
translated into application-visible errors without leaking mechanism-specific
details into domain types.

Rules:

1. Validate input at API, configuration, persistence, and external mechanism
   boundaries.
2. Preserve enough context for debugging without exposing secrets.
3. Use exceptions, result types, or status objects consistently with nearby
   code.
4. Do not use process termination, global state mutation, or logging as a
   substitute for returning an error from reusable code.
5. Do not convert unexpected failures into default success values.

Plans MUST describe error behavior for new boundary code, persistence code,
configuration parsing, and external communication surfaces.
