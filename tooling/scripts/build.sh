#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
BUILD_PRESET="${1:-${BUILD_PRESET:-debug}}"

cd "${PROJECT_ROOT}"

BUILD_DIR="${PROJECT_ROOT}/.img/build/${BUILD_PRESET}"
EXTERNAL_CACHE="${BUILD_DIR}/_deps/googletest-subbuild/CMakeCache.txt"
EXPECTED_GENERATOR="Unix Makefiles"
NEEDS_FRESH=0

if [ -f "${BUILD_DIR}/CMakeCache.txt" ] && ! grep -Fq "${PROJECT_ROOT}" "${BUILD_DIR}/CMakeCache.txt"; then
  NEEDS_FRESH=1
fi

if [ -f "${BUILD_DIR}/CMakeCache.txt" ] && ! grep -Fq "CMAKE_GENERATOR:INTERNAL=${EXPECTED_GENERATOR}" "${BUILD_DIR}/CMakeCache.txt"; then
  cmake -E rm -rf "${BUILD_DIR}/_deps"
  NEEDS_FRESH=1
fi

if [ -f "${EXTERNAL_CACHE}" ] && ! grep -Fq "${PROJECT_ROOT}" "${EXTERNAL_CACHE}"; then
  cmake -E rm -rf "${BUILD_DIR}/_deps"
  NEEDS_FRESH=1
fi

if [ -f "${EXTERNAL_CACHE}" ] && ! grep -Fq "CMAKE_GENERATOR:INTERNAL=${EXPECTED_GENERATOR}" "${EXTERNAL_CACHE}"; then
  cmake -E rm -rf "${BUILD_DIR}/_deps"
  NEEDS_FRESH=1
fi

if [ "${NEEDS_FRESH}" -eq 1 ]; then
  cmake --fresh --preset "${BUILD_PRESET}"
else
  cmake --preset "${BUILD_PRESET}" || cmake --fresh --preset "${BUILD_PRESET}"
fi

ln -sfn ".img/build/${BUILD_PRESET}/compile_commands.json" compile_commands.json
cmake --build --preset "${BUILD_PRESET}"
