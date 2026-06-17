#pragma once

#include <optional>

#include "device_id.hpp"

namespace gateway_service {

struct DeviceState {
  std::optional<DeviceId> desired;
  std::optional<DeviceId> applied;
};

}  // namespace gateway_service
