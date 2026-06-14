#include "bootstrap.hpp"

#include "../infrastructure/config/app_config.hpp"

#include "../features/channel/application/get_channel_use_case.hpp"
#include "../features/channel/application/set_channel_use_case.hpp"

#include "../features/channel/persistence/fake_radio_device.hpp"
#include "../features/channel/persistence/file_channel_config_repository.hpp"

#include <memory>

ChannelApi Bootstrap::createChannelApi() {
    AppConfig config = AppConfig::load();

    auto repository = std::make_shared<FileChannelConfigRepository>(config.channelConfigPath());

    auto radio = std::make_shared<FakeRadioDevice>();

    auto setChannelUseCase = std::make_shared<SetChannelUseCase>(*repository, *radio);

    auto getChannelUseCase = std::make_shared<GetChannelUseCase>(*repository);

    return ChannelApi(repository, radio, setChannelUseCase, getChannelUseCase);
}
