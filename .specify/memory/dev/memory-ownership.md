# Development: Memory and Ownership

C++ code MUST make ownership explicit and preserve object lifetimes.

## Rules

1. Every object or resource MUST have one clear owner.
2. Ownership and cleanup MUST use RAII wherever C++ can express the lifetime.
3. Callers MUST NOT be required to remember manual cleanup such as `delete`,
   `free`, `close`, `unlock`, or custom cleanup functions.
4. Owning raw pointers are forbidden.
5. Direct `new` and `delete` are forbidden in project-owned code except inside
   a narrowly justified RAII wrapper.
6. Heap ownership MUST be represented by `std::unique_ptr`, `std::shared_ptr`,
   a standard container, or a project-owned RAII type.
7. Use `std::unique_ptr` for exclusive heap ownership.
8. Use `std::shared_ptr` only when shared ownership is real and documented.
9. Shared ownership cycles MUST be broken with `std::weak_ptr` or removed by
   redesigning ownership.
10. Non-owning references, raw pointers, `std::string_view`, spans, and
    iterators MUST NOT outlive their owner.
11. Stored non-owning handles MUST document the owner and lifetime.
12. Ownership transfer across function, class, target, or layer boundaries
    MUST be explicit in type signatures.
13. References, pointers, `std::string_view`, spans, or iterators to
    temporaries or invalidated storage MUST NOT be returned.
14. Code that mutates a container while holding iterators, references, spans,
    or views MUST account for invalidation rules.
15. Moved-from objects MUST remain valid but unspecified. Code MUST NOT rely on
    a moved-from value except to destroy it or assign a new value.
16. Constructors and ownership-transfer operations MUST be exception-safe.

Changes that introduce new ownership, object lifetime, or view semantics MUST
state the owner, borrower, and lifetime in the plan or review notes.

Memory-sensitive changes MUST run relevant tests and SHOULD run
AddressSanitizer and UndefinedBehaviorSanitizer unless blocked.

## Required Evidence

Plans and reviews that affect ownership, lifetime, move semantics, views, or
containers MUST state:

1. Owner.
2. Borrower.
3. Lifetime boundary.
4. Ownership transfer mechanism.
5. Container invalidation behavior when applicable.
6. Test, sanitizer, or residual-risk rationale.
