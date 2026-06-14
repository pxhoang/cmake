#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
IMAGE_NAME="${IMAGE_NAME:-sample-clean-cpp-dev:latest}"

if [ "$#" -eq 0 ]; then
    set -- bash
fi

docker build \
    -t "${IMAGE_NAME}" \
    -f "${PROJECT_ROOT}/Dockerfile" \
    "${PROJECT_ROOT}"

docker run \
    --rm \
    --user "$(id -u):$(id -g)" \
    -v "${PROJECT_ROOT}:/workspace" \
    -w /workspace \
    -e HOME=/tmp \
    "${IMAGE_NAME}" \
    "$@"
