# Architecture Review

Review date: 2026-06-18

Status: completed, point-in-time review. Binding rules from this review have
been promoted into `docs/architecture/`, `docs/development/`, or
`docs/operations/`.

Scope: whole repository review with emphasis on extensibility, reuse,
dependency direction, and maintainability as the project grows beyond the
sample `gateway_service` device feature.

Processing status: completed in the follow-up architecture changes.

## Summary

The project has a strong foundation for a small C++ service skeleton:

- Feature-oriented source layout.
- Clean Architecture layering by directory and CMake target.
- A composition root for concrete adapter wiring.
- Unit, integration, and end-to-end test layers.
- Reusable CMake helpers, presets, Docker workflows, and operational docs.

The main architectural risk is that several boundaries are documented more
strongly than they are enforced. The current structure is good for a sample
project, but extension will become easier and safer if the public contracts are
narrower and dependency rules are mechanically checked.

## Implemented Changes

The review findings were processed with these changes:

- Split `application` into `application/ports` and `application/services`.
- Replaced the broad `gateway_device_application` target with
  `gateway_device_ports` and `gateway_device_services`.
- Updated adapters to depend only on `gateway_device_ports`.
- Narrowed `DeviceApi` construction to a single `DeviceService` facade.
- Moved startup mutation into an explicit `GatewayComposition::Initialize`
  lifecycle step.
- Added `tooling/scripts/check-architecture.sh` and wired it into CI.
- Replaced the service loop's interval sleep with a wakeable signal-pipe wait.
- Strengthened the e2e test to verify SIGTERM responsiveness with a long
  reconcile interval.
- Removed the unused `common::Result` placeholder library and the stale
  `protocol -> common` dependency.

## Findings

### High: Application Ports And Services Are Not Separated

Status: resolved.

Docs say adapters depend on application ports, but
`gateway_device_application` exposes the whole application directory, including
ports and concrete services. Concrete adapters link against that broad target.

Relevant files:

- `docs/architecture/dependency-rules.md`
- `src/apps/gateway_service/features/device/application/CMakeLists.txt`
- `src/apps/gateway_service/features/device/adapters/console/CMakeLists.txt`
- `src/apps/gateway_service/features/device/adapters/persistence/file/CMakeLists.txt`

Impact:

- Adapters can accidentally include and depend on services.
- The intended inward dependency direction relies on convention.
- Future feature growth can create cycles or hidden coupling.

Recommendation:

Split the application layer into narrower targets, for example:

- `gateway_device_ports`: `DeviceController`, `DeviceStateRepository`, and
  domain-facing port contracts.
- `gateway_device_services`: `SelectDeviceService`,
  `GetSelectedDeviceService`, and `ReconcileDeviceService`.

Adapters should depend on `gateway_device_ports`, not the full service target.
The API and composition root can depend on services.

### High: `DeviceApi` Exposes Composition Details

Status: resolved.

`DeviceApi` requires concrete service objects in its public constructor. This
means callers must know the internal service set and ownership model.

Relevant file:

- `src/apps/gateway_service/features/device/api/device_api.hpp`

Impact:

- Adding, removing, or splitting a service can break public API callers.
- The API facade is less reusable across CLI, daemon, HTTP, or test entry
  points.
- Construction knowledge leaks out of the composition layer.

Recommendation:

Keep `DeviceApi` as a stable facade. Hide service construction behind the
composition root or a factory. If dependency injection is still needed for
tests, expose a smaller internal constructor or inject a single service
interface instead of the full service graph.

### Medium: Bootstrap Performs Startup Behavior

Status: resolved.

`Bootstrap::CreateDeviceApi` wires objects and also mutates state by selecting
the default device or reconciling an existing desired state.

Relevant file:

- `src/apps/gateway_service/bootstrap/bootstrap.cpp`

Impact:

- Constructing an API can write persistent state and call the controller.
- Startup behavior is hard to reuse differently for one-shot, daemon, tests, or
  future network entry points.
- Composition is mixed with lifecycle policy.

Recommendation:

Keep bootstrap focused on wiring. Move initialization/reconciliation into an
explicit startup service or lifecycle function, for example:

- `GatewayLifecycle::Start(config)`
- `InitializeDeviceSelectionService`
- an explicit call from `main.cpp` after composition

This makes side effects visible at the application boundary.

### Medium: Architecture Rules Are Not Mechanically Enforced

Status: resolved for the current `gateway_service/device` feature by a
lightweight CI boundary check.

The docs state dependency rules clearly, but the current build helpers accept
arbitrary target dependencies and CI does not check the dependency graph or
include boundaries.

Relevant files:

- `docs/architecture/architecture.md`
- `docs/architecture/dependency-rules.md`
- `tooling/cmake/project_targets.cmake`
- `.github/workflows/ci.yml`

Impact:

- Future changes can violate layer rules while still building and passing
  tests.
- Reviews must manually detect architecture drift.
- Reuse quality depends on discipline rather than feedback.

Recommendation:

Add a lightweight architecture check and run it in CI. Good first checks:

- Domain targets must not depend on API, infrastructure, adapters, or vendor
  SDK targets.
- Application service targets must not depend on concrete adapters.
- Adapter targets must not include service headers if a separate ports target
  exists.
- Public include directories must not point at broad parent directories.

This can start as a script that parses `CMakeLists.txt` files and include
directives, then mature if needed.

### Medium: Service Shutdown Can Wait For The Full Interval

Status: resolved.

The daemon loop uses `std::this_thread::sleep_for(interval)`. A SIGTERM during
that sleep waits until the interval completes before the process exits.

Relevant file:

- `src/apps/gateway_service/main.cpp`

Impact:

- Default shutdown latency can be up to `RECONCILE_INTERVAL_MS`.
- Increasing the interval for production reduces operational responsiveness.
- Shutdown behavior is not isolated behind a reusable wait abstraction.

Recommendation:

Use a wakeable wait mechanism, such as a condition variable or platform event
wrapper, and test shutdown latency. Keep the wait/orchestration code at the
application or executable boundary, not in domain or service code.

### Low: `common::Result` Is Unused And `protocol` Has An Unneeded Dependency

Status: resolved.

`protocol` publicly depends on `common`, but its public header and source do not
use `common::Result`. The `Result` type is also unused elsewhere.

Relevant files:

- `src/libs/common/include/common/result.hpp`
- `src/libs/protocol/CMakeLists.txt`
- `src/libs/protocol/include/protocol/text_format.hpp`

Impact:

- Reusable library dependency surfaces are wider than necessary.
- `common` risks becoming a vague dumping ground.
- Public dependency graphs become less meaningful over time.

Recommendation:

Remove unused dependencies from `protocol`. Either remove `common::Result` until
there is a real use, or promote it into a deliberate project-wide error strategy
with clear guidance.

## Recommended Improvement Sequence

1. Split application ports from services and update adapter dependencies.
2. Narrow `DeviceApi` construction so callers depend on a stable facade.
3. Move startup side effects out of bootstrap into explicit lifecycle code.
4. Add a CI architecture-boundary check.
5. Replace sleep-based shutdown with a wakeable wait.
6. Prune unused reusable-library dependencies.

## Verification Performed

The original review included a full local build and test pass:

```bash
./tooling/scripts/test.sh
```

Result: 17/17 tests passed.

The sanitizer and warnings-as-errors preset was also run:

```bash
./tooling/scripts/test.sh sanitize
```

Result: 17/17 tests passed.

After processing the findings, the architecture boundary check was run:

```bash
./tooling/scripts/check-architecture.sh
```

Result: passed.

The full debug test suite was run again:

```bash
./tooling/scripts/test.sh
```

Result: 17/17 tests passed.

The sanitizer and warnings-as-errors preset was run again:

```bash
./tooling/scripts/test.sh sanitize
```

Result: 17/17 tests passed.

The release build was run after processing:

```bash
./tooling/scripts/build.sh release
```

Result: passed.
