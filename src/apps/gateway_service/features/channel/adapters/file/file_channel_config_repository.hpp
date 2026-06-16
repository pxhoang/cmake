#pragma once

#include <mutex>
#include <string>

#include "channel_config_repository.hpp"

namespace gateway::channel::adapter {

class FileChannelConfigRepository final
    : public application::ChannelConfigRepository {
 public:
  explicit FileChannelConfigRepository(std::string path);

  domain::ChannelState Load() override;
  void Save(const domain::ChannelState& state) override;

 private:
  domain::ChannelState LoadUnlocked();

  std::string path_;
  std::mutex mutex_;
};

}  // namespace gateway::channel::adapter
