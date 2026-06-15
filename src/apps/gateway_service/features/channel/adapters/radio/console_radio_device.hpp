#pragma once

#include "radio_device.hpp"

namespace gateway::channel::adapter {

class ConsoleRadioDevice final : public application::RadioDevice {
public:
    void applyChannel(const domain::WirelessChannel& channel) override;
};

}  // namespace gateway::channel::adapter
