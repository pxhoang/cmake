# C++ Style Guide

Projects governed by this guide favor simple, explicit C++ that keeps
ownership and layer boundaries visible.

## Namespaces

Each application uses one shared application namespace for public
application-owned C++ types. Do not mirror directory layers as nested
namespaces.

Internal reusable libraries use their library namespace when one exists.

## Headers and Includes

Headers MUST include what they use. Source files should include their matching
header first.

Use target-provided include directories. Do not rely on parent-relative include
paths to cross architecture boundaries.

## Ownership

Prefer value types for domain concepts. Use references or smart pointers for
dependencies according to surrounding code. Application use cases should accept
ports through interfaces owned by the application layer.

Do not introduce global mutable state for business behavior. Do not hide
lifetime ownership in raw owning pointers.

## Exceptions and Results

Follow nearby code for exceptions, result types, or status objects. Boundary
failures must be explicit and testable. Do not convert unexpected failures into
default success values.

## Formatting

Use repository formatting configuration. Do not introduce local formatting
styles. Keep comments focused on non-obvious decisions or constraints.
