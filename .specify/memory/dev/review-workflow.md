# Development: Review Workflow

Every change must preserve `.specify/memory/constitution.md`, architecture
memory, test placement, and repository layout.

## Workflow Rules

1. Identify affected application, feature, layer, CMake target, and repository
   area.
2. Run the Constitution Check before implementation.
3. Add or update tests before implementation tasks when behavior changes.
4. Keep edits scoped to the requested behavior.
5. Update ops, tooling, CI, and memory only when the change affects them.
6. Run the narrowest relevant verification command during development.
7. Run the full test command for shared architecture or cross-component
   behavior unless blocked.
8. For C++/Linux systems changes, document memory ownership, resource
   lifetime, thread safety, diagnostics, and platform risks.

## Review Checklist

Reviewers and agents MUST check:

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
14. Ops/memory: Are operational changes and rule changes captured?
15. Verification: Were relevant commands run or residual risk reported?

Any failed checklist item MUST be resolved before the change is considered
done. Failed non-negotiable rules cannot be waived by review comment; they
require an explicit amendment to the owning memory file.

Final summaries MUST include relevant verification commands or the reason
verification could not run.

## Required Evidence

Final reviews MUST state:

1. Constitution Check result.
2. Tests or test rationale.
3. Verification commands.
4. Residual risk.
5. Memory amendments made, if any.
6. Remaining blockers, if any.
