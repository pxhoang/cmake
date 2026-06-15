#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
BUILD_PRESET="${BUILD_PRESET:-debug}"

usage() {
  echo "Usage: $0 <binary> [args...]" >&2
}

if [ "$#" -eq 0 ]; then
  usage
  exit 2
fi

binary="$1"
shift

if [[ ! "${binary}" =~ ^[[:alnum:]_-]+$ ]] || [ ! -d "${PROJECT_ROOT}/src/apps/${binary}" ]; then
  echo "Unknown binary: ${binary}" >&2
  usage
  exit 2
fi

executable="${PROJECT_ROOT}/.img/build/${BUILD_PRESET}/src/apps/${binary}/${binary}"

if [ ! -x "${executable}" ]; then
  echo "Binary is not built: ${binary}" >&2
  echo "Run ./tooling/scripts/build.sh first." >&2
  exit 1
fi

cd "${PROJECT_ROOT}"
exec "${executable}" "$@"
