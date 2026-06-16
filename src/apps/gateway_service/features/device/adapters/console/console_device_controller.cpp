#include "console_device_controller.hpp"

#include <iostream>

namespace gateway::device::adapter {

void ConsoleDeviceController::ApplyDevice(const domain::DeviceId& device_id) {
  std::cout << "device_apply: " << device_id.Value() << std::endl;
}

}  // namespace gateway::device::adapter
