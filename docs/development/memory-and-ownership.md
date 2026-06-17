# Memory and Ownership

C++ code MUST make ownership explicit and preserve object lifetimes.

## Ownership Rules

1. Prefer RAII and value semantics.
2. Do not use owning raw pointers.
3. Use `std::unique_ptr` for exclusive ownership.
4. Use `std::shared_ptr` only when shared ownership is real and documented.
5. Use references or raw non-owning pointers only when the callee does not take
   ownership and the lifetime is obvious.
6. Do not store references or non-owning pointers beyond the lifetime of the
   referenced object.
7. Do not return references, pointers, `std::string_view`, or spans to
   temporaries or invalidated storage.

## Views and Containers

`std::string_view`, spans, iterators, and references are non-owning. Code that
stores them MUST document and test the owning lifetime.

Plans that use container mutation while holding iterators, references, spans,
or views MUST consider invalidation rules.

## Move Semantics

Moved-from objects MUST remain valid but unspecified. Code MUST NOT rely on a
moved-from value except to destroy it or assign a new value.

Ownership transfer across layer boundaries MUST be explicit in type signatures.

## Review Requirements

Changes that introduce new ownership, object lifetime, or view semantics MUST
state the owner, borrower, and lifetime in the plan or code review notes.
