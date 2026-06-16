#!/usr/bin/env bash
set -euo pipefail

runtime_dir=".img/runtime/e2e/gateway_service"
state_path="${runtime_dir}/device.state"
output_path="${runtime_dir}/service.log"
executable="${1:-./.img/build/debug/src/apps/gateway_service/gateway_service}"

rm -rf "${runtime_dir}"
mkdir -p "${runtime_dir}"

export DEVICE_STATE_PATH="${state_path}"

output="$("${executable}" once)"

echo "${output}"
grep -F "device_apply: 1" <<<"${output}"
grep -F "Current device: 1" <<<"${output}"

rm -f "${state_path}"
RECONCILE_INTERVAL_MS=50 "${executable}" serve >"${output_path}" 2>&1 &
service_pid=$!

cleanup() {
  if kill -0 "${service_pid}" 2>/dev/null; then
    kill -TERM "${service_pid}"
    wait "${service_pid}"
  fi
}
trap cleanup EXIT

for _ in {1..50}; do
  if grep -Fq "Current device: 1" "${output_path}"; then
    break
  fi

  sleep 0.02
done

grep -F "Current device: 1" "${output_path}"
kill -TERM "${service_pid}"
wait "${service_pid}"
trap - EXIT
