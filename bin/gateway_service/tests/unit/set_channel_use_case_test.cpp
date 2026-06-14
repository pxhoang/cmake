#include "features/channel/application/set_channel_use_case.hpp"

#include <gtest/gtest.h>

#include <optional>

class FakeRepository final : public ChannelConfigRepository {
public:
    void save(const WirelessChannel& channel) override {
        savedChannel = channel.value();
    }

    WirelessChannel get() override {
        return WirelessChannel(savedChannel.value());
    }

    std::optional<int> savedChannel;
};

class FakeRadio final : public RadioDevice {
public:
    void applyChannel(const WirelessChannel& channel) override {
        appliedChannel = channel.value();
    }

    std::optional<int> appliedChannel;
};

TEST(SetChannelUseCaseTest, SavesAndAppliesChannel) {
    FakeRepository repository;
    FakeRadio radio;

    SetChannelUseCase useCase(repository, radio);

    useCase.execute(15);

    ASSERT_TRUE(repository.savedChannel.has_value());
    EXPECT_EQ(repository.savedChannel.value(), 15);

    ASSERT_TRUE(radio.appliedChannel.has_value());
    EXPECT_EQ(radio.appliedChannel.value(), 15);
}
