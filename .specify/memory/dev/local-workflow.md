# Development: Local Workflow

Local development uses repository scripts and CMake presets instead of
one-off commands embedded in generated artifacts or ad hoc instructions.

## Rules

1. Local development MUST use repository scripts and CMake presets.
2. Local generated output belongs under `.img/`.
3. Workflow changes MUST preserve existing command entry points unless a
   migration is explicitly planned.
4. Product source, tests, ops assets, memory, and tooling MUST remain in
   approved repository areas.

## Common Commands

```bash
./tooling/scripts/test.sh
./tooling/scripts/test.sh tdd
./tooling/scripts/run.sh <app>
./tooling/scripts/docker-test.sh
./tooling/scripts/docker-run.sh <app>
```

## Docker Rules

1. Docker definitions MUST live under `tooling/docker/`.
2. Docker helper scripts MUST keep the repository root as the Docker build
   context.
3. Generated files from Docker workflows MUST still go under `.img/`.
4. Docker scripts SHOULD run with the host UID/GID so generated files do not
   become root-owned on the host.

Run the local or Docker command that matches the changed behavior. Report any
command that could not run and why.

## Required Evidence

Plans and reviews that change local or Docker workflow MUST state:

1. Command added or changed.
2. Generated output location.
3. Host/container path behavior when Docker is involved.
4. UID/GID behavior when Docker creates files.
5. Verification command or blocker.
