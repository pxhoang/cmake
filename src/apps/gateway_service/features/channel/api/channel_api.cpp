#include "channel_api.hpp"

#include <utility>

#include "protocol/text_format.hpp"

namespace gateway::channel::api {

ChannelApi::ChannelApi(
    std::shared_ptr<application::SetChannelUseCase> setChannelUseCase,
    std::shared_ptr<application::GetChannelUseCase> getChannelUseCase,
    std::shared_ptr<application::ReconcileChannelUseCase>
        reconcileChannelUseCase)
    : setChannelUseCase_(std::move(setChannelUseCase)),
      getChannelUseCase_(std::move(getChannelUseCase)),
      reconcileChannelUseCase_(std::move(reconcileChannelUseCase)) {}

void ChannelApi::setChannel(int channel) {
  setChannelUseCase_->execute(channel);
}

int ChannelApi::getChannel() { return getChannelUseCase_->execute().value(); }

std::string ChannelApi::getChannelMessage() {
  return protocol::formatChannelMessage(getChannel());
}

bool ChannelApi::reconcileChannel() {
  return reconcileChannelUseCase_->execute();
}

}  // namespace gateway::channel::api
