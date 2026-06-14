#include "channel_api.hpp"

#include "protocol/text_format.hpp"

#include <utility>

ChannelApi::ChannelApi(
    std::shared_ptr<ChannelConfigRepository> repository,
    std::shared_ptr<RadioDevice> radio,
    std::shared_ptr<SetChannelUseCase> setChannelUseCase,
    std::shared_ptr<GetChannelUseCase> getChannelUseCase
)
    : repository_(std::move(repository)),
      radio_(std::move(radio)),
      setChannelUseCase_(std::move(setChannelUseCase)),
      getChannelUseCase_(std::move(getChannelUseCase)) {}

void ChannelApi::setChannel(int channel) {
    setChannelUseCase_->execute(channel);
}

int ChannelApi::getChannel() {
    return getChannelUseCase_->execute().value();
}

std::string ChannelApi::getChannelMessage() {
    return protocol::formatChannelMessage(getChannel());
}
