#pragma once

#include <memory>
#include <utility>

#include "device_service.hpp"
#include "get_selected_device_service.hpp"
#include "reconcile_device_service.hpp"
#include "select_device_service.hpp"

namespace gateway_service {

class DefaultDeviceService final : public DeviceService {
 public:
  DefaultDeviceService(
      std::shared_ptr<SelectDeviceService> select_device_service,
      std::shared_ptr<GetSelectedDeviceService> get_selected_device_service,
      std::shared_ptr<ReconcileDeviceService> reconcile_device_service)
      : select_device_service_(std::move(select_device_service)),
        get_selected_device_service_(std::move(get_selected_device_service)),
        reconcile_device_service_(std::move(reconcile_device_service)) {}

  void SelectDevice(int raw_device_id) override {
    select_device_service_->Execute(raw_device_id);
  }

  DeviceId GetSelectedDevice() override {
    return get_selected_device_service_->Execute();
  }

  bool ReconcileDevice() override {
    return reconcile_device_service_->Execute();
  }

 private:
  std::shared_ptr<SelectDeviceService> select_device_service_;
  std::shared_ptr<GetSelectedDeviceService> get_selected_device_service_;
  std::shared_ptr<ReconcileDeviceService> reconcile_device_service_;
};

}  // namespace gateway_service
