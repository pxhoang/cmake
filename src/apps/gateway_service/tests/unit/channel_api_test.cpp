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

TEST(ChannelApiTest, SetsGetsAndFormatsChannel) {
  auto repository = std::make_shared<FakeRepository>();
  auto radio = std::make_shared<FakeRadio>();
  auto set_use_case = std::make_shared<SetChannelUseCase>(repository, radio);
  auto get_use_case = std::make_shared<GetChannelUseCase>(repository);
  auto reconcile_use_case =
      std::make_shared<ReconcileChannelUseCase>(repository, radio);
  ChannelApi api(set_use_case, get_use_case, reconcile_use_case);

  api.SetChannel(20);

  EXPECT_EQ(api.GetChannel(), 20);
  EXPECT_EQ(api.GetChannelMessage(), "Current channel: 20");
  ASSERT_TRUE(radio->applied_channel.has_value());
  EXPECT_EQ(radio->applied_channel->Value(), 20);
}

}  // namespace
