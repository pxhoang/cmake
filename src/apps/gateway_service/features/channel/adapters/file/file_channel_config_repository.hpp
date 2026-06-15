#pragma once

#include "channel_config_repository.hpp"

#include <mutex>
#include <string>

namespace gateway::channel::adapter {

class FileChannelConfigRepository final : public application::ChannelConfigRepository {
public:
    explicit FileChannelConfigRepository(std::string path);

    domain::ChannelState load() override;
    void save(const domain::ChannelState& state) override;

private:
    domain::ChannelState loadUnlocked();

    std::string path_;
    std::mutex mutex_;
};

}  // namespace gateway::channel::adapter
