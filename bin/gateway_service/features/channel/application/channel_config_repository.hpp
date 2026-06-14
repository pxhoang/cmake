#pragma once

#include "../domain/wireless_channel.hpp"

class ChannelConfigRepository {
public:
    virtual ~ChannelConfigRepository() = default;

    virtual void save(const WirelessChannel& channel) = 0;
    virtual WirelessChannel get() = 0;
};
