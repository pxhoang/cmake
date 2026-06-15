#include "console_radio_device.hpp"

#include <iostream>

namespace gateway::channel::adapter {

void ConsoleRadioDevice::applyChannel(const domain::WirelessChannel& channel) {
  std::cout << "radio_apply_channel: " << channel.value() << std::endl;
}

}  // namespace gateway::channel::adapter
