#include "channel_api.hpp"

#include <utility>

#include "protocol/text_format.hpp"

namespace gateway::channel::api {

ChannelApi::ChannelApi(
    std::shared_ptr<application::SetChannelUseCase> set_channel_use_case,
    std::shared_ptr<application::GetChannelUseCase> get_channel_use_case,
    std::shared_ptr<application::ReconcileChannelUseCase>
        reconcile_channel_use_case)
    : set_channel_use_case_(std::move(set_channel_use_case)),
      get_channel_use_case_(std::move(get_channel_use_case)),
      reconcile_channel_use_case_(std::move(reconcile_channel_use_case)) {}

void ChannelApi::SetChannel(int channel) {
  set_channel_use_case_->Execute(channel);
}

int ChannelApi::GetChannel() {
  return get_channel_use_case_->Execute().Value();
}

std::string ChannelApi::GetChannelMessage() {
  return protocol::FormatChannelMessage(GetChannel());
}

bool ChannelApi::ReconcileChannel() {
  return reconcile_channel_use_case_->Execute();
}

}  // namespace gateway::channel::api
