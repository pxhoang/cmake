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
            originalValue_ = value;
        }
    }

    ~EnvironmentGuard() {
        if (originalValue_.has_value()) {
            setenv(name_.c_str(), originalValue_->c_str(), 1);
        } else {
            unsetenv(name_.c_str());
        }
    }

private:
    std::string name_;
    std::optional<std::string> originalValue_;
};

TEST(AppConfigTest, LoadsDefaults) {
    EnvironmentGuard pathGuard("CHANNEL_CONFIG_PATH");
    EnvironmentGuard channelGuard("DEFAULT_CHANNEL");
    EnvironmentGuard intervalGuard("RECONCILE_INTERVAL_MS");
    unsetenv("CHANNEL_CONFIG_PATH");
    unsetenv("DEFAULT_CHANNEL");
    unsetenv("RECONCILE_INTERVAL_MS");

    const auto config = AppConfig::load();

    EXPECT_EQ(config.channelConfigPath(), ".img/runtime/gateway_service/channel.state");
    EXPECT_EQ(config.defaultChannel(), 15);
    EXPECT_EQ(config.reconcileIntervalMilliseconds(), 5000);
}

TEST(AppConfigTest, RejectsInvalidValues) {
    EnvironmentGuard pathGuard("CHANNEL_CONFIG_PATH");
    EnvironmentGuard channelGuard("DEFAULT_CHANNEL");
    EnvironmentGuard intervalGuard("RECONCILE_INTERVAL_MS");

    setenv("CHANNEL_CONFIG_PATH", "", 1);
    EXPECT_THROW(AppConfig::load(), std::runtime_error);

    setenv("CHANNEL_CONFIG_PATH", "/tmp/channel.state", 1);
    setenv("DEFAULT_CHANNEL", "99", 1);
    EXPECT_THROW(AppConfig::load(), std::invalid_argument);

    setenv("DEFAULT_CHANNEL", "15", 1);
    setenv("RECONCILE_INTERVAL_MS", "0", 1);
    EXPECT_THROW(AppConfig::load(), std::runtime_error);
}

}  // namespace
