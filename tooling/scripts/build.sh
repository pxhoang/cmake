#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
BUILD_PRESET="${1:-${BUILD_PRESET:-debug}}"

cd "${PROJECT_ROOT}"
cmake --preset "${BUILD_PRESET}"
cmake --build --preset "${BUILD_PRESET}"
