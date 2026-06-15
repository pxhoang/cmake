#include "reconcile_channel_use_case.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <optional>

namespace {

using gateway::channel::application::ChannelConfigRepository;
using gateway::channel::application::RadioDevice;
using gateway::channel::application::ReconcileChannelUseCase;
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

TEST(ReconcileChannelUseCaseTest, AppliesDesiredChannelWhenStateDiffers) {
    auto repository = std::make_shared<FakeRepository>();
    repository->state.desired = WirelessChannel(20);
    repository->state.applied = WirelessChannel(15);
    auto radio = std::make_shared<FakeRadio>();
    ReconcileChannelUseCase useCase(repository, radio);

    EXPECT_TRUE(useCase.execute());

    ASSERT_TRUE(radio->appliedChannel.has_value());
    EXPECT_EQ(radio->appliedChannel->value(), 20);
    ASSERT_TRUE(repository->state.applied.has_value());
    EXPECT_EQ(repository->state.applied->value(), 20);
}

TEST(ReconcileChannelUseCaseTest, DoesNothingWhenStateAlreadyMatches) {
    auto repository = std::make_shared<FakeRepository>();
    repository->state.desired = WirelessChannel(15);
    repository->state.applied = WirelessChannel(15);
    auto radio = std::make_shared<FakeRadio>();
    ReconcileChannelUseCase useCase(repository, radio);

    EXPECT_FALSE(useCase.execute());
    EXPECT_FALSE(radio->appliedChannel.has_value());
}

}  // namespace
