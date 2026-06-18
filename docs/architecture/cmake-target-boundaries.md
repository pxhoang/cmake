# CMake Target Boundaries

CMake targets are architecture boundaries. Every layer MUST be represented by a
narrow target that exposes only the include directories and dependencies
required by that layer contract.

## Target Naming

For an app prefix named `<app_prefix>`, feature targets MUST follow this style:

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

Target-specific `CMakeLists.txt` files belong beside their source code.
Reusable build logic belongs in `tooling/cmake/`.

Targets MUST NOT expose broad parent include paths just to make includes easy.
Targets MUST NOT add dependencies that bypass the architecture layer graph.
Parent-relative includes are forbidden when a target include directory can
express the boundary.

Plans that add or change product code MUST state the intended CMake target
graph before implementation.
