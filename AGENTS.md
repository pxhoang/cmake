# Agent Instructions

## Constitutional Docs

Agents MUST read `docs/README.md` and `docs/speckit/constitution.md` before
changing project-owned code, docs, tooling, CI, packaging, or operations assets.

`MUST`, `MUST NOT`, `forbidden`, and `required` rules in those documents and
their normative references are non-negotiable gates. Agents MUST stop and ask
for an explicit amendment when a requested change would violate one of those
rules.

## C++ Style

All agents changing project-owned C++ code MUST follow
`docs/development/cpp-style-guide.md`.

That document makes the Google C++ Style Guide the default authority:

<https://google.github.io/styleguide/cppguide.html>

Before editing `.hpp`, `.cpp`, CMake target wiring that exposes C++ headers, or
C++ tests, read the local style guide and apply both the Google rules and the
project-specific architecture rules.

Use `.clang-format` for formatting. Run relevant tests or explain why they were
not run.

## Logs

When adding or changing project-owned service logs, follow the log format in
`docs/architecture/observability.md`.
