#pragma once

#include <memory>
#include <utility>

#include "device_controller.hpp"
#include "device_state_repository.hpp"

namespace gateway::device::application {

class ReconcileDeviceUseCase {
 public:
  ReconcileDeviceUseCase(std::shared_ptr<DeviceStateRepository> repository,
                         std::shared_ptr<DeviceController> controller)
      : repository_(std::move(repository)),
        controller_(std::move(controller)) {}

  bool Execute() {
    auto state = repository_->Load();

    if (!state.desired.has_value() || state.desired == state.applied) {
      return false;
    }

    controller_->ApplyDevice(state.desired.value());
    state.applied = state.desired;
    repository_->Save(state);
    return true;
  }

 private:
  std::shared_ptr<DeviceStateRepository> repository_;
  std::shared_ptr<DeviceController> controller_;
};

}  // namespace gateway::device::application
