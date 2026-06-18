# Local Development

Local development uses repository scripts and CMake presets instead of
one-off commands embedded in feature docs.

## Ownership

This guide owns day-to-day local commands and generated-output expectations.
CMake details live in `docs/development/cmake.md`; Docker workflow details live
in `docs/development/docker.md`.

## Must

1. Local development MUST use repository scripts and CMake presets instead of
   one-off commands embedded in feature docs.
2. Local generated output belongs under `.img/`.
3. If a change alters local workflow, update `docs/development/` and preserve
   existing command entry points unless a migration is explicitly planned.

## Should

1. Prefer the narrowest command that verifies the change during local
   development.
2. Use Docker scripts when the host does not provide the required toolchain.

## Workflow

Common commands:

```bash
./tooling/scripts/test.sh
./tooling/scripts/test.sh tdd
./tooling/scripts/run.sh <app>
./tooling/scripts/docker-test.sh
./tooling/scripts/docker-run.sh <app>
```

Local cache/editor state may live in dot-directories such as `.cache/` or
`.vscode/`, but product source, tests, docs, ops assets, and tooling must
remain in their approved repository areas.

## Verification

Run the local command that matches the changed behavior. Report any command
that could not run and why.

## Related Guides

- `docs/development/cmake.md`
- `docs/development/docker.md`
- `docs/development/testing-guide.md`
