#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

cd "${PROJECT_ROOT}"

status=0

report_matches() {
  local description="$1"
  local pattern="$2"
  shift 2

  local matches
  matches="$(grep -RInE -- "$pattern" "$@" 2>/dev/null || true)"

  if [ -n "${matches}" ]; then
    echo "Architecture boundary violation: ${description}" >&2
    echo "${matches}" >&2
    status=1
  fi
}

report_source_matches() {
  local description="$1"
  local pattern="$2"
  shift 2

  local matches
  matches="$(
    grep -RInE \
      --include='*.hpp' \
      --include='*.cpp' \
      -- "$pattern" "$@" 2>/dev/null || true
  )"

  if [ -n "${matches}" ]; then
    echo "Architecture boundary violation: ${description}" >&2
    echo "${matches}" >&2
    status=1
  fi
}

device_feature="src/apps/gateway_service/features/device"

report_matches \
  "the old broad device application target must not be used in source CMake" \
  "gateway_device_application" \
  "src" \
  "tests"

report_matches \
  "device adapters must depend on ports, not services" \
  "project::gateway_device_services" \
  "${device_feature}/adapters"

report_matches \
  "device services must not depend on concrete adapters or persistence" \
  "project::gateway_device_.*(adapter|persistence)" \
  "${device_feature}/application/services"

report_matches \
  "device domain must not depend on outer device layers" \
  "project::gateway_device_(ports|services|api|.*adapter|.*persistence)" \
  "${device_feature}/domain"

report_source_matches \
  "device adapters must not include concrete service headers" \
  '#include "(default_device_service|device_service|get_selected_device_service|initialize_device_service|reconcile_device_service|select_device_service)\.hpp"' \
  "${device_feature}/adapters"

report_source_matches \
  "device services must not include concrete adapters, API, bootstrap, or config" \
  '#include "(app_config|bootstrap|console_device_controller|device_api|file_device_state_repository)\.hpp"' \
  "${device_feature}/application/services"

report_source_matches \
  "device domain must not include application, API, adapter, bootstrap, or config headers" \
  '#include "(app_config|bootstrap|console_device_controller|device_api|device_controller|device_service|device_state_repository|default_device_service|file_device_state_repository|get_selected_device_service|initialize_device_service|reconcile_device_service|select_device_service)\.hpp"' \
  "${device_feature}/domain"

if [ "${status}" -ne 0 ]; then
  exit "${status}"
fi

echo "Architecture boundary check passed."
