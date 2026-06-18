# C++ Style Guide

Project C++ code follows the Google C++ Style Guide:

<https://google.github.io/styleguide/cppguide.html>

The Google guide is the default authority for naming, headers, includes,
scoping, classes, functions, ownership, comments, formatting, and language
feature choices. Local rules in this document are project-specific additions
for architecture and repository layout. If this document conflicts with the
Google guide, this document wins only for the explicitly stated local rule.

## Ownership

This guide owns project C++ style, naming, headers, includes, local C++ rules,
and formatting expectations. Memory ownership details live in
`docs/development/memory-and-ownership.md`; CMake target wiring lives in
`docs/development/cmake.md`.

## Must

1. Agents changing C++ code MUST read and apply this file before editing
   source, headers, CMake target wiring that exposes headers, or tests.
2. Formatting MUST use `.clang-format`, which is based on Google style.
3. Static checks MUST use `.clang-tidy` where applicable.
4. Code review MUST reject C++ changes that conflict with the Google guide or
   the local rules below.
5. Generated or third-party code may keep its upstream style, but project-owned
   wrappers around it MUST follow this guide.
6. Headers MUST include what they use.
7. Use target-provided include directories. Do not rely on parent-relative
   include paths to cross architecture boundaries.
8. Do not introduce global mutable state for business behavior.
9. Do not hide lifetime ownership in raw owning pointers.

## Should

1. When unsure, use the stricter interpretation and mention the uncertainty in
   the change summary.
2. Prefer direct includes over forward declarations unless there is a concrete
   compile-time or dependency-boundary reason.
3. Do not forward declare symbols from namespaces the project does not own.
4. Prefer value types for domain concepts.
5. Use references or smart pointers for dependencies according to surrounding
   code.
6. Application services should accept ports through interfaces owned by the
   application layer.
7. Follow nearby code for exceptions, result types, or status objects.
8. Keep comments focused on non-obvious decisions or constraints.
9. Source files should include their matching header first.

## Workflow

### Namespaces

Each application uses one shared application namespace for public
application-owned C++ types. Do not mirror directory layers as nested
namespaces.

Internal reusable libraries use their library namespace when one exists.

### Headers and Includes

Headers MUST include what they use. Source files should include their matching
header first.

Prefer direct includes over forward declarations unless there is a concrete
compile-time or dependency-boundary reason. Do not forward declare symbols from
namespaces the project does not own.

Use target-provided include directories. Do not rely on parent-relative include
paths to cross architecture boundaries.

### Local Ownership Rules

Prefer value types for domain concepts. Use references or smart pointers for
dependencies according to surrounding code. Application services should accept
ports through interfaces owned by the application layer.

Do not introduce global mutable state for business behavior. Do not hide
lifetime ownership in raw owning pointers.

### Exceptions and Results

Follow nearby code for exceptions, result types, or status objects. Boundary
failures must be explicit and testable. Do not convert unexpected failures into
default success values.

### Formatting

Use repository formatting configuration. Do not introduce local formatting
styles. Keep comments focused on non-obvious decisions or constraints.

## Verification

C++ changes SHOULD run formatting, relevant tests, and applicable static
analysis. If they cannot run, report the blocker and residual risk.

## Related Guides

- `docs/development/memory-and-ownership.md`
- `docs/development/static-analysis.md`
- `docs/development/cmake.md`
