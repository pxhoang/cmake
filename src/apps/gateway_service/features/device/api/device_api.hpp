#pragma once

#include <memory>
#include <string>

#include "get_selected_device_use_case.hpp"
#include "reconcile_device_use_case.hpp"
#include "select_device_use_case.hpp"

namespace gateway_service {

class DeviceApi {
 public:
  DeviceApi(
      std::shared_ptr<SelectDeviceUseCase> select_device_use_case,
      std::shared_ptr<GetSelectedDeviceUseCase> get_selected_device_use_case,
      std::shared_ptr<ReconcileDeviceUseCase> reconcile_device_use_case);

  void SelectDevice(int device_id);
  int GetSelectedDevice();
  std::string GetSelectedDeviceMessage();
  bool ReconcileDevice();

 private:
  std::shared_ptr<SelectDeviceUseCase> select_device_use_case_;
  std::shared_ptr<GetSelectedDeviceUseCase> get_selected_device_use_case_;
  std::shared_ptr<ReconcileDeviceUseCase> reconcile_device_use_case_;
};

}  // namespace gateway_service
