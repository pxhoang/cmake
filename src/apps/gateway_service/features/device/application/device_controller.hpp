#pragma once

#include "device_id.hpp"

namespace gateway_service {

class DeviceController {
 public:
  virtual ~DeviceController() = default;

  virtual void ApplyDevice(const DeviceId& device_id) = 0;
};

}  // namespace gateway_service
