#include "console_device_controller.hpp"

#include <iostream>

namespace gateway_service {

void ConsoleDeviceController::ApplyDevice(const DeviceId& device_id) {
  std::cout << "device_apply: " << device_id.Value() << std::endl;
}

}  // namespace gateway_service
