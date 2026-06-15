#include "channel_api.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <optional>

namespace {

using gateway::channel::api::ChannelApi;
using gateway::channel::application::ChannelConfigRepository;
using gateway::channel::application::GetChannelUseCase;
using gateway::channel::application::RadioDevice;
using gateway::channel::application::ReconcileChannelUseCase;
using gateway::channel::application::SetChannelUseCase;
using gateway::channel::domain::ChannelState;
using gateway::channel::domain::WirelessChannel;

class FakeRepository final : public ChannelConfigRepository {
public:
    ChannelState load() override {
        return state;
    }

    void save(const ChannelState& value) override {
        state = value;
    }

    ChannelState state;
};

class FakeRadio final : public RadioDevice {
public:
    void applyChannel(const WirelessChannel& channel) override {
        appliedChannel = channel;
    }

    std::optional<WirelessChannel> appliedChannel;
};

TEST(ChannelApiTest, SetsGetsAndFormatsChannel) {
    auto repository = std::make_shared<FakeRepository>();
    auto radio = std::make_shared<FakeRadio>();
    auto setUseCase = std::make_shared<SetChannelUseCase>(repository, radio);
    auto getUseCase = std::make_shared<GetChannelUseCase>(repository);
    auto reconcileUseCase = std::make_shared<ReconcileChannelUseCase>(repository, radio);
    ChannelApi api(setUseCase, getUseCase, reconcileUseCase);

    api.setChannel(20);

    EXPECT_EQ(api.getChannel(), 20);
    EXPECT_EQ(api.getChannelMessage(), "Current channel: 20");
    ASSERT_TRUE(radio->appliedChannel.has_value());
    EXPECT_EQ(radio->appliedChannel->value(), 20);
}

}  // namespace
