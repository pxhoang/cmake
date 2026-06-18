# Docker Development Environment

This project can be built, tested, and run inside Docker so the host machine
does not need CMake, Make, or a C++ compiler installed.

The only host requirement is Docker.

## Ownership

This guide owns Docker-based developer workflows. Docker assets live under
`tooling/docker/`; local non-Docker workflow lives in
`docs/development/local-development.md`.

## Must

1. Docker definitions MUST live under `tooling/docker/`.
2. Docker helper scripts MUST keep the repository root as the Docker build
   context.
3. Generated files from Docker workflows MUST still go under `.img/`.

## Should

1. Prefer the shell scripts over direct Docker Compose for repeatable developer
   and CI workflows.
2. Preserve path-stable mounts so editor compile databases and CMake caches
   remain usable on the host.
3. Run containers with the host UID/GID so generated files do not become
   root-owned on the host.

## Workflow

### Build inside Docker

```bash
./tooling/scripts/docker-build.sh
```

### Test inside Docker

```bash
./tooling/scripts/docker-test.sh
```

### Run inside Docker

```bash
./tooling/scripts/docker-run.sh <app>
```

For the current sample application:

```bash
./tooling/scripts/docker-run.sh gateway_service
```

### Open an interactive build shell

```bash
./tooling/scripts/docker-shell.sh
```

Inside the shell, you can run:

```bash
./tooling/scripts/test.sh
./tooling/scripts/run.sh <app>
```

Both run commands accept any application directory under `src/apps/`:

```bash
./tooling/scripts/run.sh <binary> [args...]
./tooling/scripts/docker-run.sh <binary> [args...]
```

Docker definitions live under `tooling/docker/`. The helper scripts keep the
repository root as the Docker build context.

The shell scripts are the preferred Docker entry point because they mount the
repository at the same absolute path inside the container. Direct Docker Compose
usage is supported for ad hoc shells, but the scripts are what keep editor
compile databases and CMake caches path-stable.

### Output Policy

The container bind-mounts the project at the same absolute path used by the
host. That keeps CMake caches and `compile_commands.json` usable by editors on
the host. All generated files still go to `.img/` in the project root.

Examples:

```text
.img/build/debug/
.img/runtime/<app>/
.img/package/
```

The Docker scripts run the container using the host UID/GID, so generated
files should not become root-owned on the host.

## Verification

Run the Docker helper script affected by the change. If Docker is unavailable,
report the skipped command and residual risk.

## Related Guides

- `docs/development/local-development.md`
- `docs/development/build-tooling-packaging.md`
- `docs/development/cmake.md`
