# Code Review Checklist

Reviewers and agents MUST check the constitution gates and the relevant
normative guides.

## Checklist

1. Scope: Does the change stay within approved product scope?
2. Architecture: Are feature layers and bootstrap composition preserved?
3. Dependencies: Do all dependencies point inward?
4. CMake: Do targets enforce the intended boundaries?
5. API/handlers: Are boundaries thin and free of business rules?
6. Memory: Is ownership explicit and lifetime-safe?
7. Resources: Are Linux resources RAII-owned and cleaned up?
8. Concurrency: Are data races, shutdown, and blocking behavior addressed?
9. Errors: Are failures explicit and testable?
10. Observability: Are diagnostics useful and secret-safe?
11. Security: Are inputs validated and secrets excluded?
12. Tests: Are the right test layers present?
13. Tooling: Are generated outputs under `.img/`?
14. Docs/ops: Are behavior and operational changes documented?
15. Verification: Were relevant commands run or residual risk reported?

Any failed checklist item must be resolved or explicitly escalated before the
change is considered done.
