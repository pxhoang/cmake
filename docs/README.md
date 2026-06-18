# Documentation Index

These documents are constitutional inputs for Spec Kit and agent work. They are
not optional background material.

## Constitutional Force

Durable rules in `docs/architecture/`, `docs/development/`, and
`docs/operations/` feed the project constitution.

1. `MUST`, `MUST NOT`, `forbidden`, and `required` rules are non-negotiable.
2. A plan, task list, implementation, review, or generated artifact that
   violates a non-negotiable rule is blocked.
3. Non-negotiable rules can be changed only by explicit human approval and a
   constitution or guide amendment.
4. `SHOULD` rules are expected defaults. Deviations require an explicit
   rationale, impact, and verification plan.
5. Convenience, generated suggestions, local shortcuts, and agent preferences
   never override these documents.

## Ownership

Use the narrowest owning document:

1. `docs/architecture/` owns what must be true about the system.
2. `docs/development/` owns how engineers implement and verify changes.
3. `docs/operations/` owns how deployed services are configured, run, secured,
   and maintained.
4. `docs/adr/` owns accepted architecture decisions and rationale.
5. `docs/reviews/` owns point-in-time audits and reviews. Durable findings must
   be promoted into architecture, development, or operations guides.
6. `docs/speckit/` owns constitution and planning examples.

## Spec Kit Mapping

Spec Kit artifacts must use these docs as binding input:

1. Constitution: cite the non-negotiable gates and normative references from
   `docs/speckit/constitution.md`.
2. Specification: capture product scope, user-visible behavior, operational
   outcome, security, observability, persistence, and testability impact.
3. Plan: include a Constitution Check with PASS, FAIL, or N/A and evidence for
   every gate.
4. Tasks: order enforcement, tests, implementation, docs/ops/tooling updates,
   and verification so failed gates are found before implementation proceeds.
5. Checklists: include concrete checks from the relevant owning guides.
6. Implementation: stop on non-negotiable violations and amend the governing
   document before continuing.

## Reading Order

For any feature or change, read:

1. `docs/speckit/constitution.md`
2. `docs/architecture/source-layout.md`
3. The architecture guide for the affected boundary.
4. The development guide for the implementation mechanism.
5. The operations guide for deployed runtime impact.
6. `docs/development/code-review-checklist.md`
