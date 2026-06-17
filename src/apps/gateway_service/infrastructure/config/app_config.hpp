#pragma once

#include <string>

namespace gateway_service {

class AppConfig {
 public:
  static AppConfig Load();

  const std::string& DeviceStatePath() const;
  int DefaultDeviceId() const;
  int ReconcileIntervalMilliseconds() const;

 private:
  AppConfig(std::string device_state_path, int default_device_id,
            int reconcile_interval_milliseconds);

  std::string device_state_path_;
  int default_device_id_;
  int reconcile_interval_milliseconds_;
};

}  // namespace gateway_service
