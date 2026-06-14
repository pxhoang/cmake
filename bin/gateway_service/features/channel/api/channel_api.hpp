#pragma once

#include "../application/channel_config_repository.hpp"
#include "../application/get_channel_use_case.hpp"
#include "../application/radio_device.hpp"
#include "../application/set_channel_use_case.hpp"

#include <memory>
#include <string>

class ChannelApi {
public:
    ChannelApi(
        std::shared_ptr<ChannelConfigRepository> repository,
        std::shared_ptr<RadioDevice> radio,
        std::shared_ptr<SetChannelUseCase> setChannelUseCase,
        std::shared_ptr<GetChannelUseCase> getChannelUseCase
    );

    void setChannel(int channel);
    int getChannel();
    std::string getChannelMessage();

private:
    std::shared_ptr<ChannelConfigRepository> repository_;
    std::shared_ptr<RadioDevice> radio_;
    std::shared_ptr<SetChannelUseCase> setChannelUseCase_;
    std::shared_ptr<GetChannelUseCase> getChannelUseCase_;
};
