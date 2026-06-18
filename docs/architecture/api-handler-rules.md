# API / IPC / Handler Rules

The default application API is an in-process C++ function-call API. API code is
an input adapter. It translates caller input into application service calls
and translates service output into caller-facing responses.

API, IPC, and handler code MUST:

1. Depend on application services, not concrete adapters.
2. Keep protocol parsing and formatting outside domain and application logic.
3. Validate caller input at the boundary before invoking services.
4. Avoid owning business rules, persistence rules, retry policies, or mechanism
   details.
5. Return explicit success or failure information.

New TCP, HTTP, RPC, message bus, CLI command router, plugin, or background
handler surfaces MUST be introduced as adapters with explicit ports, tests,
configuration, security considerations, timeout behavior, and CMake target
boundaries.

Handlers MUST NOT be added directly inside domain or application code.
