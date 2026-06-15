#include "file_channel_config_repository.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <thread>

#include <unistd.h>

namespace {

using gateway::channel::adapter::FileChannelConfigRepository;
using gateway::channel::domain::ChannelState;
using gateway::channel::domain::WirelessChannel;

class FileChannelConfigRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        directory = std::filesystem::path(".img/runtime/tests") /
                    ("file_channel_config_repository_" + std::to_string(::getpid()));
        path = directory / "channel.state";
        std::filesystem::remove_all(directory);
    }

    void TearDown() override {
        std::filesystem::remove_all(directory);
    }

    std::filesystem::path directory;
    std::filesystem::path path;
};

TEST_F(FileChannelConfigRepositoryTest, ReturnsEmptyStateWhenFileDoesNotExist) {
    FileChannelConfigRepository repository(path.string());

    const auto state = repository.load();

    EXPECT_FALSE(state.desired.has_value());
    EXPECT_FALSE(state.applied.has_value());
}

TEST_F(FileChannelConfigRepositoryTest, SavesAndLoadsState) {
    FileChannelConfigRepository repository(path.string());
    const ChannelState expected{WirelessChannel(15), WirelessChannel(20)};

    repository.save(expected);
    const auto loaded = repository.load();

    ASSERT_TRUE(loaded.desired.has_value());
    EXPECT_EQ(loaded.desired->value(), 15);
    ASSERT_TRUE(loaded.applied.has_value());
    EXPECT_EQ(loaded.applied->value(), 20);
}

TEST_F(FileChannelConfigRepositoryTest, RejectsCorruptState) {
    std::filesystem::create_directories(directory);
    std::ofstream(path) << "invalid\n";
    FileChannelConfigRepository repository(path.string());

    EXPECT_THROW(repository.load(), std::runtime_error);
}

TEST_F(FileChannelConfigRepositoryTest, SerializesConcurrentWrites) {
    FileChannelConfigRepository repository(path.string());

    std::thread first([&repository] {
        repository.save(ChannelState{WirelessChannel(15), WirelessChannel(15)});
    });
    std::thread second([&repository] {
        repository.save(ChannelState{WirelessChannel(20), WirelessChannel(20)});
    });

    first.join();
    second.join();

    const auto state = repository.load();
    ASSERT_TRUE(state.desired.has_value());
    ASSERT_TRUE(state.applied.has_value());
    EXPECT_EQ(state.desired, state.applied);
    EXPECT_TRUE(state.desired->value() == 15 || state.desired->value() == 20);
}

}  // namespace
