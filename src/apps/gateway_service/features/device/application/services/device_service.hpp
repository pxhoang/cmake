#pragma once

#include "device_id.hpp"

namespace gateway_service {

class DeviceService {
 public:
  virtual ~DeviceService() = default;

  virtual void SelectDevice(int raw_device_id) = 0;
  virtual DeviceId GetSelectedDevice() = 0;
  virtual bool ReconcileDevice() = 0;
};

}  // namespace gateway_service
