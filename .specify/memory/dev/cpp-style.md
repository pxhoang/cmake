# Development: C++ Style

Project-owned C++ code MUST follow the Google C++ Style Guide:

```text
https://google.github.io/styleguide/cppguide.html
```

Local rules in `.specify/memory/` are project-specific additions. If local
memory conflicts with the Google guide, local memory wins only for the
explicitly stated project constraint.

## Rules

1. Formatting MUST use `.clang-format`, which is based on Google style.
2. Static checks MUST use `.clang-tidy` where applicable.
3. Headers MUST include what they use.
4. Source files SHOULD include their matching header first.
5. Prefer direct includes over forward declarations unless there is a concrete
   compile-time or dependency-boundary reason.
6. Symbols from namespaces the project does not own MUST NOT be forward
   declared.
7. Use target-provided include directories.
8. Parent-relative include paths MUST NOT be used to cross architecture
   boundaries.
9. Global mutable state MUST NOT be introduced for business behavior.
10. Lifetime ownership MUST NOT be hidden in raw owning pointers.
11. Prefer value types for domain concepts.
12. Application services SHOULD accept ports through interfaces owned by the
    application layer.
13. Boundary failures MUST be explicit and testable.
14. Unexpected failures MUST NOT be converted into default success values.
15. Comments SHOULD explain non-obvious decisions or constraints.

Project-owned wrappers around generated or third-party code MUST follow this
memory even when upstream code keeps its original style.

## Required Evidence

C++ plans and reviews MUST state:

1. Whether project-owned C++ code is affected.
2. Formatting command or reason formatting could not run.
3. Static check command when applicable.
4. Any local rule that intentionally overrides general Google C++ guidance.
5. Include or namespace boundary decisions when they are non-obvious.
