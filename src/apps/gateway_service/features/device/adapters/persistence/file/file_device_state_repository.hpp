#pragma once

#include <mutex>
#include <string>

#include "device_state_repository.hpp"

namespace gateway_service {

class FileDeviceStateRepository final : public DeviceStateRepository {
 public:
  explicit FileDeviceStateRepository(std::string path);

  DeviceState Load() override;
  void Save(const DeviceState& state) override;

 private:
  DeviceState LoadUnlocked();

  std::string path_;
  std::mutex mutex_;
};

}  // namespace gateway_service
