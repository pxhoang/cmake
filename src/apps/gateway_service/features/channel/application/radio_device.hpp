#pragma once

#include "wireless_channel.hpp"

namespace gateway::channel::application {

class RadioDevice {
 public:
  virtual ~RadioDevice() = default;

  virtual void ApplyChannel(const domain::WirelessChannel& channel) = 0;
};

}  // namespace gateway::channel::application
