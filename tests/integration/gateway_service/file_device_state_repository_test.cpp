#include "file_device_state_repository.hpp"

#include <gtest/gtest.h>
#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <thread>

namespace {

using gateway::device::domain::DeviceId;
using gateway::device::domain::DeviceState;
using gateway::device::persistence::FileDeviceStateRepository;

class FileDeviceStateRepositoryTest : public ::testing::Test {
 protected:
  void SetUp() override {
    directory = std::filesystem::path(".img/runtime/tests") /
                ("file_device_state_repository_" + std::to_string(::getpid()));
    path = directory / "device.state";
    std::filesystem::remove_all(directory);
  }

  void TearDown() override { std::filesystem::remove_all(directory); }

  std::filesystem::path directory;
  std::filesystem::path path;
};

TEST_F(FileDeviceStateRepositoryTest, ReturnsEmptyStateWhenFileDoesNotExist) {
  FileDeviceStateRepository repository(path.string());

  const auto state = repository.Load();

  EXPECT_FALSE(state.desired.has_value());
  EXPECT_FALSE(state.applied.has_value());
}

TEST_F(FileDeviceStateRepositoryTest, SavesAndLoadsState) {
  FileDeviceStateRepository repository(path.string());
  const DeviceState expected{DeviceId(15), DeviceId(20)};

  repository.Save(expected);
  const auto loaded = repository.Load();

  ASSERT_TRUE(loaded.desired.has_value());
  EXPECT_EQ(loaded.desired->Value(), 15);
  ASSERT_TRUE(loaded.applied.has_value());
  EXPECT_EQ(loaded.applied->Value(), 20);
}

TEST_F(FileDeviceStateRepositoryTest, RejectsCorruptState) {
  std::filesystem::create_directories(directory);
  std::ofstream(path) << "invalid\n";
  FileDeviceStateRepository repository(path.string());

  EXPECT_THROW(repository.Load(), std::runtime_error);
}

TEST_F(FileDeviceStateRepositoryTest, SerializesConcurrentWrites) {
  FileDeviceStateRepository repository(path.string());

  std::thread first([&repository] {
    repository.Save(DeviceState{DeviceId(15), DeviceId(15)});
  });
  std::thread second([&repository] {
    repository.Save(DeviceState{DeviceId(20), DeviceId(20)});
  });

  first.join();
  second.join();

  const auto state = repository.Load();
  ASSERT_TRUE(state.desired.has_value());
  ASSERT_TRUE(state.applied.has_value());
  EXPECT_EQ(state.desired, state.applied);
  EXPECT_TRUE(state.desired->Value() == 15 || state.desired->Value() == 20);
}

}  // namespace
