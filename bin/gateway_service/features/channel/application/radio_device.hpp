#pragma once

#include "../domain/wireless_channel.hpp"

class RadioDevice {
public:
    virtual ~RadioDevice() = default;

    virtual void applyChannel(const WirelessChannel& channel) = 0;
};
