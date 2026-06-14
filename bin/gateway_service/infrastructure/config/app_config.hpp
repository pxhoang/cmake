#pragma once

#include <string>

class AppConfig {
public:
    static AppConfig load();

    const std::string& channelConfigPath() const;

private:
    explicit AppConfig(std::string channelConfigPath);

    std::string channelConfigPath_;
};
