#pragma once

#include <string>

namespace gateway::infrastructure {

class AppConfig {
 public:
  static AppConfig Load();

  const std::string& ChannelConfigPath() const;
  int DefaultChannel() const;
  int ReconcileIntervalMilliseconds() const;

 private:
  AppConfig(std::string channel_config_path, int default_channel,
            int reconcile_interval_milliseconds);

  std::string channel_config_path_;
  int default_channel_;
  int reconcile_interval_milliseconds_;
};

}  // namespace gateway::infrastructure
