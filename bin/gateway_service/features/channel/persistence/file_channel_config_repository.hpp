#pragma once

#include "../application/channel_config_repository.hpp"

#include <string>

class FileChannelConfigRepository final : public ChannelConfigRepository {
public:
    explicit FileChannelConfigRepository(std::string path);

    void save(const WirelessChannel& channel) override;
    WirelessChannel get() override;

private:
    std::string path_;
};
