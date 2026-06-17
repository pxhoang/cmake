# Docker Development Environment

This project can be built, tested, and run inside Docker so the host machine
does not need CMake, Make, or a C++ compiler installed.

The only host requirement is Docker.

## Build inside Docker

```bash
./tooling/scripts/docker-build.sh
```

## Test inside Docker

```bash
./tooling/scripts/docker-test.sh
```

## Run inside Docker

```bash
./tooling/scripts/docker-run.sh gateway_service
```

Expected output:

```text
device_apply: 1
Current device: 1
```

## Open an interactive build shell

```bash
./tooling/scripts/docker-shell.sh
```

Inside the shell, you can run:

```bash
./tooling/scripts/test.sh
./tooling/scripts/run.sh gateway_service
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

## Output policy

The container bind-mounts the project at the same absolute path used by the
host. That keeps CMake caches and `compile_commands.json` usable by editors on
the host. All generated files still go to `.img/` in the project root.

Examples:

```text
.img/build/debug/
.img/runtime/gateway_service/device.state
.img/package/
```

The Docker scripts run the container using the host UID/GID, so generated files should not become root-owned on the host.
