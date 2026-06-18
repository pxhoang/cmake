# Architecture: CMake Targets

CMake targets are architecture boundaries. Every affected layer and concrete
mechanism MUST be represented by a narrow target that exposes only the include
directories and dependencies required by that layer or mechanism contract.

## Target Naming

For an app prefix named `<app_prefix>`, feature targets MUST follow this style
when the corresponding layer or mechanism exists:

```text
<app_prefix>_<feature>_domain
<app_prefix>_<feature>_ports
<app_prefix>_<feature>_services
<app_prefix>_<feature>_api
<app_prefix>_<feature>_<adapter>_adapter
<app_prefix>_<feature>_<persistence>_persistence
<app_prefix>_composition
```

## Rules

1. Target-specific `CMakeLists.txt` files belong beside their source code.
2. Reusable build logic belongs in `tooling/cmake/`.
3. Targets MUST NOT expose broad parent include paths just to make includes
   easy.
4. Targets MUST NOT add dependencies that bypass the architecture layer graph.
5. Parent-relative includes are forbidden when a target include directory can
   express the boundary.

Plans that add or change product code MUST state the intended CMake target
graph before implementation.

## Required Evidence

Plans and reviews that add or change CMake targets MUST state:

1. Target name.
2. Target layer.
3. Source-local `CMakeLists.txt` path.
4. Public include directories exposed by the target.
5. Direct dependencies linked by the target.
6. Why any `PUBLIC` dependency is exposed by public headers.
