# Deployment

`gateway_service` can be installed as a systemd service.

The service runs `gateway_service serve`, handles SIGTERM, and periodically
reconciles desired channel state with applied device state.

Repository-owned configuration and deployment assets live under `ops/config/`
and `ops/deploy/`.

Runtime config is provided through:

```text
/etc/gateway_service/gateway_service.env
```

Default production state is stored at:

```text
/var/lib/gateway_service/channel.state
```

The systemd unit creates this directory through `StateDirectory`.

Generated package output must be created under:

```text
.img/package/
```

Build a release package with:

```bash
cmake --preset release
cmake --build --preset release
cpack --config .img/build/release/CPackConfig.cmake -B .img/package
```
