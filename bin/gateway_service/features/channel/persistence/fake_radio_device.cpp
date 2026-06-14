#include "fake_radio_device.hpp"

#include <iostream>

void FakeRadioDevice::applyChannel(const WirelessChannel& channel) {
    std::cout << "radio_apply_channel: " << channel.value() << "\n";
}
