#include "features/channel/api/channel_api.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <optional>

class FakeRepository final : public ChannelConfigRepository {
public:
    void save(const WirelessChannel& channel) override {
        currentChannel = channel.value();
    }

    WirelessChannel get() override {
        return WirelessChannel(currentChannel.value());
    }

    std::optional<int> currentChannel;
};

class FakeRadio final : public RadioDevice {
public:
    void applyChannel(const WirelessChannel& channel) override {
        appliedChannel = channel.value();
    }

    std::optional<int> appliedChannel;
};

TEST(ChannelApiTest, SetsAndGetsChannel) {
    auto repository = std::make_shared<FakeRepository>();
    auto radio = std::make_shared<FakeRadio>();

    auto setUseCase = std::make_shared<SetChannelUseCase>(*repository, *radio);
    auto getUseCase = std::make_shared<GetChannelUseCase>(*repository);

    ChannelApi api(repository, radio, setUseCase, getUseCase);

    api.setChannel(20);

    EXPECT_EQ(api.getChannel(), 20);
    EXPECT_EQ(api.getChannelMessage(), "Current channel: 20");

    ASSERT_TRUE(radio->appliedChannel.has_value());
    EXPECT_EQ(radio->appliedChannel.value(), 20);
}
