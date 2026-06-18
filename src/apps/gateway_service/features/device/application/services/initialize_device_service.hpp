#pragma once

#include <memory>
#include <utility>

#include "device_state_repository.hpp"
#include "reconcile_device_service.hpp"
#include "select_device_service.hpp"

namespace gateway_service {

class InitializeDeviceService {
 public:
  InitializeDeviceService(
      std::shared_ptr<DeviceStateRepository> repository,
      std::shared_ptr<SelectDeviceService> select_device_service,
      std::shared_ptr<ReconcileDeviceService> reconcile_device_service)
      : repository_(std::move(repository)),
        select_device_service_(std::move(select_device_service)),
        reconcile_device_service_(std::move(reconcile_device_service)) {}

  void Execute(int default_device_id) {
    const auto state = repository_->Load();

    if (!state.desired.has_value()) {
      select_device_service_->Execute(default_device_id);
      return;
    }

    reconcile_device_service_->Execute();
  }

 private:
  std::shared_ptr<DeviceStateRepository> repository_;
  std::shared_ptr<SelectDeviceService> select_device_service_;
  std::shared_ptr<ReconcileDeviceService> reconcile_device_service_;
};

}  // namespace gateway_service
