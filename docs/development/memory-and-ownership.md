# Memory and Ownership

C++ code MUST make ownership explicit and preserve object lifetimes.

## Ownership

This guide owns C++ object ownership, lifetime, move semantics, views,
containers, and smart pointer usage. Linux resource ownership lives in
`docs/development/resource-lifetime.md`; thread ownership lives in
`docs/development/thread-safety.md`.

## Must

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
12. Ownership transfer across function, class, target, or layer boundaries MUST
    be explicit in type signatures.
13. Do not return references, pointers, `std::string_view`, spans, or iterators
    to temporaries or invalidated storage.
14. Code that mutates a container while holding iterators, references, spans, or
    views MUST account for invalidation rules.
15. Moved-from objects MUST remain valid but unspecified. Code MUST NOT rely on
    a moved-from value except to destroy it or assign a new value.
16. Constructors and ownership-transfer operations MUST be exception-safe.
17. Changes that introduce new ownership, object lifetime, or view semantics
    MUST state the owner, borrower, and lifetime in the plan or code review
    notes.
18. Memory-sensitive changes MUST run relevant tests and SHOULD run
    AddressSanitizer and UndefinedBehaviorSanitizer unless blocked.

## Should

1. Prefer value semantics and stack objects over heap allocation.
2. Prefer `std::make_unique` and `std::make_shared` over raw allocation.
3. Prefer `const T&` for required non-owning inputs.
4. Prefer `T*` only for nullable non-owning inputs.
5. Prefer return values over output parameters or borrowed output views.
6. Keep `std::shared_ptr` out of domain value types unless ownership truly
   requires sharing.
7. Avoid storing references as members. Prefer values, IDs, smart pointers, or
   explicit handles with clear ownership.
8. Keep ownership local to the smallest layer that needs it.
9. Add tests for lifetime-sensitive behavior, ownership transfer, failure
   paths, and cleanup.
10. Add comments only where ownership is not obvious from the type.

## Workflow

### Views and Containers

`std::string_view`, spans, iterators, raw pointers, and references are
non-owning. Storing them is allowed only when the owner and lifetime are
explicit and testable.

Container operations may invalidate iterators, references, pointers, and spans.
Code that mutates containers while holding non-owning handles MUST document why
the handles remain valid or reacquire them after mutation.

### Smart Pointers

Use `std::unique_ptr<T>` when one owner controls lifetime. Pass it by value only
when transferring ownership.

Use `std::shared_ptr<T>` only when multiple owners extend the object's
lifetime. Passing `std::shared_ptr<T>` across a boundary means the callee may
share ownership. If the callee only observes the object, pass `T&`, `const T&`,
or `T*` instead.

Use `std::weak_ptr<T>` for back-references, observer relationships, caches, and
other cases where shared ownership would create a cycle.

### Review Notes

Changes that introduce new ownership, object lifetime, or view semantics MUST
state the owner, borrower, and lifetime in the plan or code review notes.

## Verification

Reviewers and agents MUST verify:

1. Ownership is visible from the type signature or documented at the narrowest
   practical point.
2. Failure paths release owned resources.
3. No borrowed handle can outlive its owner.
4. No container invalidation bug is introduced.
5. Tests or sanitizer runs cover the risky lifetime behavior, or residual risk
   is reported.

## Related Guides

- `docs/development/resource-lifetime.md`
- `docs/development/thread-safety.md`
- `docs/development/static-analysis.md`
