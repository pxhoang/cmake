#pragma once

#include "app_config.hpp"
#include "device_api.hpp"

namespace gateway::bootstrap {

class Bootstrap {
 public:
  device::api::DeviceApi CreateDeviceApi(
      const infrastructure::AppConfig& config);
};

}  // namespace gateway::bootstrap
