#include "set_channel_use_case.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

namespace {

using gateway::channel::application::ChannelConfigRepository;
using gateway::channel::application::RadioDevice;
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
        if (fail) {
            throw std::runtime_error("radio_failed");
        }

        appliedChannel = channel;
    }

    bool fail = false;
    std::optional<WirelessChannel> appliedChannel;
};

TEST(SetChannelUseCaseTest, PersistsDesiredAndAppliedChannel) {
    auto repository = std::make_shared<FakeRepository>();
    auto radio = std::make_shared<FakeRadio>();
    SetChannelUseCase useCase(repository, radio);

    useCase.execute(15);

    ASSERT_TRUE(repository->state.desired.has_value());
    EXPECT_EQ(repository->state.desired->value(), 15);
    ASSERT_TRUE(repository->state.applied.has_value());
    EXPECT_EQ(repository->state.applied->value(), 15);
    ASSERT_TRUE(radio->appliedChannel.has_value());
    EXPECT_EQ(radio->appliedChannel->value(), 15);
}

TEST(SetChannelUseCaseTest, PreservesDesiredStateWhenRadioFails) {
    auto repository = std::make_shared<FakeRepository>();
    auto radio = std::make_shared<FakeRadio>();
    radio->fail = true;
    SetChannelUseCase useCase(repository, radio);

    EXPECT_THROW(useCase.execute(20), std::runtime_error);

    ASSERT_TRUE(repository->state.desired.has_value());
    EXPECT_EQ(repository->state.desired->value(), 20);
    EXPECT_FALSE(repository->state.applied.has_value());
}

}  // namespace
