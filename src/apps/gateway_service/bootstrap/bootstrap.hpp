#pragma once

#include "app_config.hpp"
#include "device_api.hpp"

namespace gateway_service {

class Bootstrap {
 public:
  DeviceApi CreateDeviceApi(const AppConfig& config);
};

}  // namespace gateway_service
