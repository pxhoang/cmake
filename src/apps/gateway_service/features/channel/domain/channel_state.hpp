#pragma once

#include "wireless_channel.hpp"

#include <optional>

namespace gateway::channel::domain {

struct ChannelState {
    std::optional<WirelessChannel> desired;
    std::optional<WirelessChannel> applied;
};

}  // namespace gateway::channel::domain
