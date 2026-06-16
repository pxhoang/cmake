#pragma once

#include <memory>
#include <utility>

#include "device_controller.hpp"
#include "device_state_repository.hpp"

namespace gateway::device::application {

class SelectDeviceUseCase {
 public:
  SelectDeviceUseCase(std::shared_ptr<DeviceStateRepository> repository,
                      std::shared_ptr<DeviceController> controller)
      : repository_(std::move(repository)),
        controller_(std::move(controller)) {}

  void Execute(int raw_device_id) {
    const domain::DeviceId device_id(raw_device_id);
    auto state = repository_->Load();

    state.desired = device_id;
    repository_->Save(state);

    controller_->ApplyDevice(device_id);

    state.applied = device_id;
    repository_->Save(state);
  }

 private:
  std::shared_ptr<DeviceStateRepository> repository_;
  std::shared_ptr<DeviceController> controller_;
};

}  // namespace gateway::device::application
