#include "bootstrap.hpp"

#include "console_radio_device.hpp"
#include "file_channel_config_repository.hpp"
#include "get_channel_use_case.hpp"
#include "reconcile_channel_use_case.hpp"
#include "set_channel_use_case.hpp"

#include <memory>

namespace gateway::bootstrap {

channel::api::ChannelApi Bootstrap::createChannelApi(const infrastructure::AppConfig& config) {
    auto repository =
        std::make_shared<channel::adapter::FileChannelConfigRepository>(config.channelConfigPath());
    auto radio = std::make_shared<channel::adapter::ConsoleRadioDevice>();

    auto setChannelUseCase =
        std::make_shared<channel::application::SetChannelUseCase>(repository, radio);
    auto getChannelUseCase =
        std::make_shared<channel::application::GetChannelUseCase>(repository);
    auto reconcileChannelUseCase =
        std::make_shared<channel::application::ReconcileChannelUseCase>(repository, radio);

    if (!repository->load().desired.has_value()) {
        setChannelUseCase->execute(config.defaultChannel());
    } else {
        reconcileChannelUseCase->execute();
    }

    return channel::api::ChannelApi(
        setChannelUseCase,
        getChannelUseCase,
        reconcileChannelUseCase
    );
}

}  // namespace gateway::bootstrap
