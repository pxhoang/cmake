# Architecture: API, IPC, and Handlers

When a feature exposes an application API, the default application API is an
in-process C++ function-call API. API code is an input adapter. It translates
caller input into application service calls and translates service output into
caller-facing responses.

## Rules

When introduced, API, IPC, CLI, plugin, background handler, and service handler
code MUST:

1. Depend on application services, not concrete adapters.
2. Keep protocol parsing and formatting outside domain and application logic.
3. Validate caller input at the boundary before invoking services.
4. MUST NOT own business rules, persistence rules, retry policies, or
   mechanism details.
5. Return explicit success or failure information.

New TCP, HTTP, RPC, message bus, CLI command router, plugin, or background
handler surfaces MUST be introduced as concrete boundary mechanisms with:

1. Explicit ports.
2. Tests.
3. Configuration.
4. Security considerations.
5. Timeout behavior.
6. CMake target boundaries.

Handlers MUST NOT be added directly inside domain or application code.

## Required Evidence

Plans and reviews that add or change API, IPC, CLI, plugin, background
handler, or service handler code MUST state:

1. Surface type.
2. Adapter location.
3. Application service invoked by the adapter.
4. Input validation behavior.
5. Success and failure response behavior.
6. Timeout, retry, and cancellation behavior when applicable.
7. Security checks for external surfaces.
