#pragma once

#include "device_controller.hpp"

namespace gateway::device::adapter {

class ConsoleDeviceController final : public application::DeviceController {
 public:
  void ApplyDevice(const domain::DeviceId& device_id) override;
};

}  // namespace gateway::device::adapter
