#!/usr/bin/env bash
set -euo pipefail

export CHANNEL_CONFIG_PATH=".img/runtime/e2e/gateway_service/channel.txt"

output="$(./.img/build/debug/bin/gateway_service/gateway_service)"

echo "$output"

echo "$output" | grep "radio_apply_channel: 15"
echo "$output" | grep "Current channel: 15"
