#pragma once

#include <optional>

#include "wireless_channel.hpp"

namespace gateway::channel::domain {

struct ChannelState {
  std::optional<WirelessChannel> desired;
  std::optional<WirelessChannel> applied;
};

}  // namespace gateway::channel::domain
