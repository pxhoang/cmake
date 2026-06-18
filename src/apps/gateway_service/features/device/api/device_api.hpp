#pragma once

#include <memory>
#include <string>

#include "device_service.hpp"

namespace gateway_service {

class DeviceApi {
 public:
  explicit DeviceApi(std::shared_ptr<DeviceService> device_service);

  void SelectDevice(int device_id);
  int GetSelectedDevice();
  std::string GetSelectedDeviceMessage();
  bool ReconcileDevice();

 private:
  std::shared_ptr<DeviceService> device_service_;
};

}  // namespace gateway_service
