#pragma once

#include "channel_config_repository.hpp"

#include <memory>
#include <stdexcept>
#include <utility>

namespace gateway::channel::application {

class GetChannelUseCase {
public:
    explicit GetChannelUseCase(std::shared_ptr<ChannelConfigRepository> repository)
        : repository_(std::move(repository)) {}

    domain::WirelessChannel execute() {
        const auto state = repository_->load();

        if (!state.desired.has_value()) {
            throw std::runtime_error("desired_channel_not_configured");
        }

        return state.desired.value();
    }

private:
    std::shared_ptr<ChannelConfigRepository> repository_;
};

}  // namespace gateway::channel::application
