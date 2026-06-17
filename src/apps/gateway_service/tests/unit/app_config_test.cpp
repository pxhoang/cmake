#include "app_config.hpp"

#include <gtest/gtest.h>

#include <cstdlib>
#include <optional>
#include <string>

namespace {

using gateway_service::AppConfig;

class EnvironmentGuard {
 public:
  explicit EnvironmentGuard(const char* name) : name_(name) {
    const char* value = std::getenv(name);

    if (value != nullptr) {
      original_value_ = value;
    }
  }

  ~EnvironmentGuard() {
    if (original_value_.has_value()) {
      setenv(name_.c_str(), original_value_->c_str(), 1);
    } else {
      unsetenv(name_.c_str());
    }
  }

 private:
  std::string name_;
  std::optional<std::string> original_value_;
};

TEST(AppConfigTest, LoadsDefaults) {
  EnvironmentGuard path_guard("DEVICE_STATE_PATH");
  EnvironmentGuard device_id_guard("DEFAULT_DEVICE_ID");
  EnvironmentGuard interval_guard("RECONCILE_INTERVAL_MS");
  unsetenv("DEVICE_STATE_PATH");
  unsetenv("DEFAULT_DEVICE_ID");
  unsetenv("RECONCILE_INTERVAL_MS");

  const auto config = AppConfig::Load();

  EXPECT_EQ(config.DeviceStatePath(),
            ".img/runtime/gateway_service/device.state");
  EXPECT_EQ(config.DefaultDeviceId(), 1);
  EXPECT_EQ(config.ReconcileIntervalMilliseconds(), 5000);
}

TEST(AppConfigTest, RejectsInvalidValues) {
  EnvironmentGuard path_guard("DEVICE_STATE_PATH");
  EnvironmentGuard device_id_guard("DEFAULT_DEVICE_ID");
  EnvironmentGuard interval_guard("RECONCILE_INTERVAL_MS");

  setenv("DEVICE_STATE_PATH", "", 1);
  EXPECT_THROW(AppConfig::Load(), std::runtime_error);

  setenv("DEVICE_STATE_PATH", "/tmp/device.state", 1);
  setenv("DEFAULT_DEVICE_ID", "999", 1);
  EXPECT_THROW(AppConfig::Load(), std::invalid_argument);

  setenv("DEFAULT_DEVICE_ID", "1", 1);
  setenv("RECONCILE_INTERVAL_MS", "0", 1);
  EXPECT_THROW(AppConfig::Load(), std::runtime_error);
}

}  // namespace
