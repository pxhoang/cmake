#pragma once

#include "channel_config_repository.hpp"
#include "radio_device.hpp"

class SetChannelUseCase {
public:
    SetChannelUseCase(ChannelConfigRepository& repository, RadioDevice& radio)
        : repository_(repository), radio_(radio) {}

    void execute(int rawChannel) {
        WirelessChannel channel(rawChannel);

        repository_.save(channel);
        radio_.applyChannel(channel);
    }

private:
    ChannelConfigRepository& repository_;
    RadioDevice& radio_;
};
