# Local Development

Local development uses repository scripts and CMake presets instead of
one-off commands embedded in feature docs.

Common commands:

```bash
./tooling/scripts/test.sh
./tooling/scripts/test.sh tdd
./tooling/scripts/run.sh <app>
./tooling/scripts/docker-test.sh
./tooling/scripts/docker-run.sh <app>
```

Local generated output belongs under `.img/`. Local cache/editor state may live
in dot-directories such as `.cache/` or `.vscode/`, but product source, tests,
docs, ops assets, and tooling must remain in their approved repository areas.

If a change alters local workflow, update `docs/development/` and preserve
existing command entry points unless a migration is explicitly planned.
