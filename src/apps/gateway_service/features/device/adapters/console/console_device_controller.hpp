#pragma once

#include "device_controller.hpp"

namespace gateway_service {

class ConsoleDeviceController final : public DeviceController {
 public:
  void ApplyDevice(const DeviceId& device_id) override;
};

}  // namespace gateway_service
