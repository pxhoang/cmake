# Docker Development Environment

This project can be built, tested, and run inside Docker so the host machine does not need CMake, Ninja, or a C++ compiler installed.

The only host requirement is Docker.

## Build inside Docker

```bash
./scripts/docker-build.sh
```

## Test inside Docker

```bash
./scripts/docker-test.sh
```

## Run inside Docker

```bash
./scripts/docker-run.sh gateway_service
```

Expected output:

```text
radio_apply_channel: 15
Current channel: 15
```

## Open an interactive build shell

```bash
./scripts/docker-shell.sh
```

Inside the shell, you can run:

```bash
./scripts/test.sh
./scripts/run.sh gateway_service
```

Both run commands accept any application directory under `bin/`:

```bash
./scripts/run.sh <binary> [args...]
./scripts/docker-run.sh <binary> [args...]
```

## Output policy

The container bind-mounts the project into `/workspace`.
All generated files still go to `.img/` in the project root.

Examples:

```text
.img/build/debug/
.img/runtime/gateway_service/channel.txt
.img/package/
```

The Docker scripts run the container using the host UID/GID, so generated files should not become root-owned on the host.
