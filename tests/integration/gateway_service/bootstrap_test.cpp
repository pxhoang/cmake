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
           ("bootstrap_" + std::to_string(::getpid())) / "device.state";
    std::filesystem::remove_all(path.parent_path());

    setenv("DEVICE_STATE_PATH", path.c_str(), 1);
    setenv("DEFAULT_DEVICE_ID", "20", 1);
    setenv("RECONCILE_INTERVAL_MS", "50", 1);
  }

  void TearDown() override {
    unsetenv("DEVICE_STATE_PATH");
    unsetenv("DEFAULT_DEVICE_ID");
    unsetenv("RECONCILE_INTERVAL_MS");
    std::filesystem::remove_all(path.parent_path());
  }

  std::filesystem::path path;
};

TEST_F(BootstrapTest, WiresAdaptersAndInitializesDefaultDeviceId) {
  const auto config = gateway_service::AppConfig::Load();
  gateway_service::Bootstrap bootstrap;

  auto composition = bootstrap.Create(config);
  composition.Initialize(config);

  EXPECT_EQ(composition.Device().GetSelectedDevice(), 20);
  EXPECT_TRUE(std::filesystem::exists(path));
}

}  // namespace
