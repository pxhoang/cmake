#pragma once

#include "channel_state.hpp"

namespace gateway::channel::application {

class ChannelConfigRepository {
 public:
  virtual ~ChannelConfigRepository() = default;

  virtual domain::ChannelState Load() = 0;
  virtual void Save(const domain::ChannelState& state) = 0;
};

}  // namespace gateway::channel::application
