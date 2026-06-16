#include "app_config.hpp"

#include <gtest/gtest.h>

#include <cstdlib>
#include <optional>
#include <string>

namespace {

using gateway::infrastructure::AppConfig;

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
  EnvironmentGuard path_guard("CHANNEL_CONFIG_PATH");
  EnvironmentGuard channel_guard("DEFAULT_CHANNEL");
  EnvironmentGuard interval_guard("RECONCILE_INTERVAL_MS");
  unsetenv("CHANNEL_CONFIG_PATH");
  unsetenv("DEFAULT_CHANNEL");
  unsetenv("RECONCILE_INTERVAL_MS");

  const auto config = AppConfig::Load();

  EXPECT_EQ(config.ChannelConfigPath(),
            ".img/runtime/gateway_service/channel.state");
  EXPECT_EQ(config.DefaultChannel(), 15);
  EXPECT_EQ(config.ReconcileIntervalMilliseconds(), 5000);
}

TEST(AppConfigTest, RejectsInvalidValues) {
  EnvironmentGuard path_guard("CHANNEL_CONFIG_PATH");
  EnvironmentGuard channel_guard("DEFAULT_CHANNEL");
  EnvironmentGuard interval_guard("RECONCILE_INTERVAL_MS");

  setenv("CHANNEL_CONFIG_PATH", "", 1);
  EXPECT_THROW(AppConfig::Load(), std::runtime_error);

  setenv("CHANNEL_CONFIG_PATH", "/tmp/channel.state", 1);
  setenv("DEFAULT_CHANNEL", "99", 1);
  EXPECT_THROW(AppConfig::Load(), std::invalid_argument);

  setenv("DEFAULT_CHANNEL", "15", 1);
  setenv("RECONCILE_INTERVAL_MS", "0", 1);
  EXPECT_THROW(AppConfig::Load(), std::runtime_error);
}

}  // namespace
