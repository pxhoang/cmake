# Memory Index

This directory contains binding constitutional memory for Spec Kit and agents.
It is self-contained.

Start with binding memory:

1. `.specify/memory/constitution.md`
2. The section index for the affected area.
3. The focused rule file for the affected topic.

## File Standard

Each binding rule file under `arch/`, `dev/`, and `ops/` MUST be suitable for
direct use as constitutional input:

1. It MUST state the owned topic.
2. It MUST state binding rules with `MUST`, `MUST NOT`, `SHOULD`,
   `forbidden`, or `required`.
3. It MUST state required evidence when the topic can be affected by a plan,
   task, implementation, or review.
4. It MUST NOT depend on non-memory files as the source of authority.
5. It MUST be small enough to amend without unrelated rule churn.

Samples under `samples/` are validation artifacts. They MUST demonstrate how
binding memory is applied, and they MUST NOT introduce new constitutional
rules.

## Sections

Architecture:

1. `.specify/memory/arch/README.md`
2. `.specify/memory/arch/*.md`

Development:

1. `.specify/memory/dev/README.md`
2. `.specify/memory/dev/*.md`

Operations:

1. `.specify/memory/ops/README.md`
2. `.specify/memory/ops/*.md`

Samples:

1. `.specify/memory/samples/README.md`
2. `.specify/memory/samples/*.md`

When another project artifact disagrees with memory, memory wins for
constitutional gates.
