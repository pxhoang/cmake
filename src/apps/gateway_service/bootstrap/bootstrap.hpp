#pragma once

#include <functional>

#include "app_config.hpp"
#include "device_api.hpp"

namespace gateway_service {

class GatewayComposition {
 public:
  GatewayComposition(DeviceApi device_api,
                     std::function<void(int)> initialize_device);

  void Initialize(const AppConfig& config);
  DeviceApi& Device();

 private:
  DeviceApi device_api_;
  std::function<void(int)> initialize_device_;
};

class Bootstrap {
 public:
  GatewayComposition Create(const AppConfig& config);
};

}  // namespace gateway_service
