#pragma once

#include <optional>

#include "device_id.hpp"

namespace gateway::device::domain {

struct DeviceState {
  std::optional<DeviceId> desired;
  std::optional<DeviceId> applied;
};

}  // namespace gateway::device::domain
