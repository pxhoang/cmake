#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
TEST_PRESET="${1:-${TEST_PRESET:-debug}}"

case "${TEST_PRESET}" in
    tdd)
        BUILD_PRESET=tdd
        ;;
    debug|unit|integration|e2e)
        BUILD_PRESET=debug
        ;;
    sanitize)
        BUILD_PRESET=sanitize
        ;;
    *)
        echo "Unknown test preset: ${TEST_PRESET}" >&2
        echo "Expected one of: tdd, debug, unit, integration, e2e, sanitize" >&2
        exit 2
        ;;
esac

cd "${PROJECT_ROOT}"
cmake --preset "${BUILD_PRESET}"
cmake --build --preset "${BUILD_PRESET}"
ctest --preset "${TEST_PRESET}"
