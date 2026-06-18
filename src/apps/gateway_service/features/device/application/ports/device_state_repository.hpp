#pragma once

#include "device_state.hpp"

namespace gateway_service {

class DeviceStateRepository {
 public:
  virtual ~DeviceStateRepository() = default;

  virtual DeviceState Load() = 0;
  virtual void Save(const DeviceState& state) = 0;
};

}  // namespace gateway_service
