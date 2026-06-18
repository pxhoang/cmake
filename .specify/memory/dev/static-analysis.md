# Development: Static Analysis and Sanitizers

Static analysis and sanitizers are part of quality enforcement.

## Rules

1. Compiler warnings MUST remain enabled.
2. Warning suppressions MUST be narrow and justified.
3. Suppressions MUST include a reason and the smallest practical scope.
4. Broad project-wide suppressions are not allowed without explicit approval.
5. Plans that cannot run relevant analysis MUST report the command, blocker,
   and residual risk.

`clang-tidy` findings SHOULD be fixed unless the finding is documented as not
applicable.

AddressSanitizer and UndefinedBehaviorSanitizer SHOULD be run for memory,
ownership, parser, container, or low-level changes.

ThreadSanitizer SHOULD be considered for concurrency changes.

Leak checks SHOULD be considered for long-running service changes.

Report the exact analysis or sanitizer command run. If the command cannot run,
report the blocker and residual risk.

## Required Evidence

Plans and reviews MUST state:

1. Warning, static-analysis, or sanitizer command run when applicable.
2. Suppression scope and reason when a suppression is added.
3. Sanitizer selected for memory, concurrency, parser, container, or low-level
   changes.
4. Blocker and residual risk when analysis cannot run.
