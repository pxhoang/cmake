#pragma once

#include <mutex>
#include <string>

#include "device_state_repository.hpp"

namespace gateway::device::persistence {

class FileDeviceStateRepository final
    : public application::DeviceStateRepository {
 public:
  explicit FileDeviceStateRepository(std::string path);

  domain::DeviceState Load() override;
  void Save(const domain::DeviceState& state) override;

 private:
  domain::DeviceState LoadUnlocked();

  std::string path_;
  std::mutex mutex_;
};

}  // namespace gateway::device::persistence
