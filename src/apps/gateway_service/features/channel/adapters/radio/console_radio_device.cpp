#include "console_radio_device.hpp"

#include <iostream>

namespace gateway::channel::adapter {

void ConsoleRadioDevice::ApplyChannel(const domain::WirelessChannel& channel) {
  std::cout << "radio_apply_channel: " << channel.Value() << std::endl;
}

}  // namespace gateway::channel::adapter
