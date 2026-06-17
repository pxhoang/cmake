# Static Analysis and Sanitizers

Static analysis and sanitizers are part of quality enforcement.

## Required Practices

1. Compiler warnings MUST remain enabled.
2. Warning suppressions MUST be narrow and justified.
3. `clang-tidy` findings SHOULD be fixed unless the finding is documented as
   not applicable.
4. AddressSanitizer and UndefinedBehaviorSanitizer SHOULD be run for memory,
   ownership, parser, container, or low-level changes.
5. ThreadSanitizer SHOULD be considered for concurrency changes.
6. Leak checks SHOULD be considered for long-running service changes.

## Suppressions

Suppressions MUST include a reason and the smallest practical scope. Broad
project-wide suppressions are not allowed without explicit approval.

Plans that cannot run relevant analysis MUST report the command, blocker, and
residual risk.
