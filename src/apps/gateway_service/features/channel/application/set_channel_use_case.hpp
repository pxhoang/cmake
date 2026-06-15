#pragma once

#include "channel_config_repository.hpp"
#include "radio_device.hpp"

#include <memory>
#include <utility>

namespace gateway::channel::application {

class SetChannelUseCase {
public:
    SetChannelUseCase(
        std::shared_ptr<ChannelConfigRepository> repository,
        std::shared_ptr<RadioDevice> radio
    )
        : repository_(std::move(repository)), radio_(std::move(radio)) {}

    void execute(int rawChannel) {
        const domain::WirelessChannel channel(rawChannel);
        auto state = repository_->load();

        state.desired = channel;
        repository_->save(state);

        radio_->applyChannel(channel);

        state.applied = channel;
        repository_->save(state);
    }

private:
    std::shared_ptr<ChannelConfigRepository> repository_;
    std::shared_ptr<RadioDevice> radio_;
};

}  // namespace gateway::channel::application
