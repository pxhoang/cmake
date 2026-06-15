#pragma once

#include <string>

namespace gateway::infrastructure {

class AppConfig {
public:
    static AppConfig load();

    const std::string& channelConfigPath() const;
    int defaultChannel() const;
    int reconcileIntervalMilliseconds() const;

private:
    AppConfig(
        std::string channelConfigPath,
        int defaultChannel,
        int reconcileIntervalMilliseconds
    );

    std::string channelConfigPath_;
    int defaultChannel_;
    int reconcileIntervalMilliseconds_;
};

}  // namespace gateway::infrastructure
