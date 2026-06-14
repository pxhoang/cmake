#include "app_config.hpp"

#include <cstdlib>
#include <utility>

AppConfig::AppConfig(std::string channelConfigPath)
    : channelConfigPath_(std::move(channelConfigPath)) {}

AppConfig AppConfig::load() {
    const char* value = std::getenv("CHANNEL_CONFIG_PATH");

    if (value != nullptr) {
        return AppConfig(value);
    }

    return AppConfig(".img/runtime/gateway_service/channel.txt");
}

const std::string& AppConfig::channelConfigPath() const {
    return channelConfigPath_;
}
