#include "features/channel/persistence/file_channel_config_repository.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <string>

class FileChannelConfigRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::filesystem::remove(path);
    }

    void TearDown() override {
        std::filesystem::remove(path);
    }

    const std::string path = ".img/runtime/tests/file_channel_config_repository/channel.txt";
};

TEST_F(FileChannelConfigRepositoryTest, SavesAndLoadsChannel) {
    FileChannelConfigRepository repository(path);

    repository.save(WirelessChannel(15));

    const WirelessChannel loaded = repository.get();

    EXPECT_EQ(loaded.value(), 15);
}
