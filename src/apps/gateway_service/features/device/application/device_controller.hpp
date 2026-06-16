#pragma once

#include "device_id.hpp"

namespace gateway::device::application {

class DeviceController {
 public:
  virtual ~DeviceController() = default;

  virtual void ApplyDevice(const domain::DeviceId& device_id) = 0;
};

}  // namespace gateway::device::application
