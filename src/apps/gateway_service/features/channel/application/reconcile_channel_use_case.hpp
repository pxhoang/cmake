#pragma once

#include <memory>
#include <utility>

#include "channel_config_repository.hpp"
#include "radio_device.hpp"

namespace gateway::channel::application {

class ReconcileChannelUseCase {
 public:
  ReconcileChannelUseCase(std::shared_ptr<ChannelConfigRepository> repository,
                          std::shared_ptr<RadioDevice> radio)
      : repository_(std::move(repository)), radio_(std::move(radio)) {}

  bool execute() {
    auto state = repository_->load();

    if (!state.desired.has_value() || state.desired == state.applied) {
      return false;
    }

    radio_->applyChannel(state.desired.value());
    state.applied = state.desired;
    repository_->save(state);
    return true;
  }

 private:
  std::shared_ptr<ChannelConfigRepository> repository_;
  std::shared_ptr<RadioDevice> radio_;
};

}  // namespace gateway::channel::application
