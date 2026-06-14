#pragma once

#include "channel_config_repository.hpp"

class GetChannelUseCase {
public:
    explicit GetChannelUseCase(ChannelConfigRepository& repository) : repository_(repository) {}

    WirelessChannel execute() {
        return repository_.get();
    }

private:
    ChannelConfigRepository& repository_;
};
