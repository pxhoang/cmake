#pragma once

#include <memory>
#include <utility>

#include "channel_config_repository.hpp"
#include "radio_device.hpp"

namespace gateway::channel::application {

class SetChannelUseCase {
 public:
  SetChannelUseCase(std::shared_ptr<ChannelConfigRepository> repository,
                    std::shared_ptr<RadioDevice> radio)
      : repository_(std::move(repository)), radio_(std::move(radio)) {}

  void Execute(int raw_channel) {
    const domain::WirelessChannel channel(raw_channel);
    auto state = repository_->Load();

    state.desired = channel;
    repository_->Save(state);

    radio_->ApplyChannel(channel);

    state.applied = channel;
    repository_->Save(state);
  }

 private:
  std::shared_ptr<ChannelConfigRepository> repository_;
  std::shared_ptr<RadioDevice> radio_;
};

}  // namespace gateway::channel::application
