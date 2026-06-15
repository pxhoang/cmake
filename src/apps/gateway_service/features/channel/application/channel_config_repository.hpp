#pragma once

#include "channel_state.hpp"

namespace gateway::channel::application {

class ChannelConfigRepository {
 public:
  virtual ~ChannelConfigRepository() = default;

  virtual domain::ChannelState load() = 0;
  virtual void save(const domain::ChannelState& state) = 0;
};

}  // namespace gateway::channel::application
