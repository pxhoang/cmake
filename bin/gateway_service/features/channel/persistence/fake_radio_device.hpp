#pragma once

#include "../application/radio_device.hpp"

class FakeRadioDevice final : public RadioDevice {
public:
    void applyChannel(const WirelessChannel& channel) override;
};
