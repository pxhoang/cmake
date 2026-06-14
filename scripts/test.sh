#!/usr/bin/env bash
set -euo pipefail

cmake --preset debug
cmake --build --preset debug
ctest --test-dir .img/build/debug --output-on-failure
