#include "bootstrap.hpp"

#include <gtest/gtest.h>
#include <unistd.h>

#include <cstdlib>
#include <filesystem>
#include <string>

#include "app_config.hpp"

namespace {

class BootstrapTest : public ::testing::Test {
 protected:
  void SetUp() override {
    path = std::filesystem::path(".img/runtime/tests") /
           ("bootstrap_" + std::to_string(::getpid())) / "channel.state";
    std::filesystem::remove_all(path.parent_path());

    setenv("CHANNEL_CONFIG_PATH", path.c_str(), 1);
    setenv("DEFAULT_CHANNEL", "20", 1);
    setenv("RECONCILE_INTERVAL_MS", "50", 1);
  }

  void TearDown() override {
    unsetenv("CHANNEL_CONFIG_PATH");
    unsetenv("DEFAULT_CHANNEL");
    unsetenv("RECONCILE_INTERVAL_MS");
    std::filesystem::remove_all(path.parent_path());
  }

  std::filesystem::path path;
};

TEST_F(BootstrapTest, WiresAdaptersAndInitializesDefaultChannel) {
  const auto config = gateway::infrastructure::AppConfig::load();
  gateway::bootstrap::Bootstrap bootstrap;

  auto api = bootstrap.createChannelApi(config);

  EXPECT_EQ(api.getChannel(), 20);
  EXPECT_TRUE(std::filesystem::exists(path));
}

}  // namespace
