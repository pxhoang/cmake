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
  ChannelState Load() override { return state; }

  void Save(const ChannelState& value) override { state = value; }

  ChannelState state;
};

class FakeRadio final : public RadioDevice {
 public:
  void ApplyChannel(const WirelessChannel& channel) override {
    applied_channel = channel;
  }

  std::optional<WirelessChannel> applied_channel;
};

TEST(ReconcileChannelUseCaseTest, AppliesDesiredChannelWhenStateDiffers) {
  auto repository = std::make_shared<FakeRepository>();
  repository->state.desired = WirelessChannel(20);
  repository->state.applied = WirelessChannel(15);
  auto radio = std::make_shared<FakeRadio>();
  ReconcileChannelUseCase useCase(repository, radio);

  EXPECT_TRUE(useCase.Execute());

  ASSERT_TRUE(radio->applied_channel.has_value());
  EXPECT_EQ(radio->applied_channel->Value(), 20);
  ASSERT_TRUE(repository->state.applied.has_value());
  EXPECT_EQ(repository->state.applied->Value(), 20);
}

TEST(ReconcileChannelUseCaseTest, DoesNothingWhenStateAlreadyMatches) {
  auto repository = std::make_shared<FakeRepository>();
  repository->state.desired = WirelessChannel(15);
  repository->state.applied = WirelessChannel(15);
  auto radio = std::make_shared<FakeRadio>();
  ReconcileChannelUseCase useCase(repository, radio);

  EXPECT_FALSE(useCase.Execute());
  EXPECT_FALSE(radio->applied_channel.has_value());
}

}  // namespace
