#pragma once

#include <memory>
#include <stdexcept>
#include <utility>

#include "device_state_repository.hpp"

namespace gateway_service {

class GetSelectedDeviceService {
 public:
  explicit GetSelectedDeviceService(
      std::shared_ptr<DeviceStateRepository> repository)
      : repository_(std::move(repository)) {}

  DeviceId Execute() {
    const auto state = repository_->Load();

    if (!state.desired.has_value()) {
      throw std::runtime_error("desired_device_not_configured");
    }

    return state.desired.value();
  }

 private:
  std::shared_ptr<DeviceStateRepository> repository_;
};

}  // namespace gateway_service
