# Contributing

Every change must preserve the constitution, architecture guides, test
placement, and repository layout.

## Required Workflow

1. Identify affected application, feature, layer, CMake target, and repository
   area.
2. Run the Constitution Check before implementation.
3. Add or update tests before implementation tasks when behavior changes.
4. Keep edits scoped to the requested behavior.
5. Update docs, ops, tooling, and CI only when the change affects them.
6. Run the narrowest relevant verification command, and run the full test
   command for shared architecture or cross-component behavior.

## Definition of Done

A change is done only when:

1. Constitution gates pass.
2. Tests or documented test rationale are present.
3. Generated output remains under `.img/`.
4. Documentation and operations assets match actual behavior.
5. Verification results and residual risk are reported.

Temporary architecture violations are not allowed.
