#pragma once

#include "device_state.hpp"

namespace gateway::device::application {

class DeviceStateRepository {
 public:
  virtual ~DeviceStateRepository() = default;

  virtual domain::DeviceState Load() = 0;
  virtual void Save(const domain::DeviceState& state) = 0;
};

}  // namespace gateway::device::application
