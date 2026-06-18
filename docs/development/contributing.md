# Contributing

Every change must preserve the constitution, architecture guides, test
placement, and repository layout.

## Ownership

This guide owns the expected development workflow and definition of done.
Review details live in `docs/development/code-review-checklist.md`; test-layer
selection lives in `docs/development/testing-guide.md`.

## Must

1. Every change MUST preserve the constitution, architecture guides, test
   placement, and repository layout.
2. Temporary architecture violations are not allowed.
3. Non-negotiable guide rules MUST NOT be bypassed for convenience, generated
   suggestions, local shortcuts, or agent preference.
4. A change is done only when the verification criteria below are satisfied.

## Should

1. Keep edits scoped to the requested behavior.
2. Run the narrowest relevant verification command during development.
3. Run the full test command for shared architecture or cross-component
   behavior.

## Workflow

1. Identify affected application, feature, layer, CMake target, and repository
   area.
2. Run the Constitution Check before implementation.
3. Add or update tests before implementation tasks when behavior changes.
4. Keep edits scoped to the requested behavior.
5. Update docs, ops, tooling, and CI only when the change affects them.
6. Run the narrowest relevant verification command, and run the full test
   command for shared architecture or cross-component behavior.
7. For C++/Linux systems changes, document memory ownership, resource
   lifetime, thread safety, diagnostics, and platform risks.

## Verification

A change is done only when:

1. Constitution gates pass.
2. Tests or documented test rationale are present.
3. Generated output remains under `.img/`.
4. Documentation and operations assets match actual behavior.
5. Verification results and residual risk are reported.
6. Memory, resource, concurrency, security, and Linux runtime risks are handled
   or explicitly reported.
7. Any requested exception to a non-negotiable rule has an approved amendment
   to the owning guide or constitution.

## Related Guides

- `docs/speckit/constitution.md`
- `docs/development/code-review-checklist.md`
- `docs/development/testing-guide.md`
