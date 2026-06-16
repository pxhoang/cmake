#include "bootstrap.hpp"

#include <memory>

#include "console_radio_device.hpp"
#include "file_channel_config_repository.hpp"
#include "get_channel_use_case.hpp"
#include "reconcile_channel_use_case.hpp"
#include "set_channel_use_case.hpp"

namespace gateway::bootstrap {

channel::api::ChannelApi Bootstrap::CreateChannelApi(
    const infrastructure::AppConfig& config) {
  auto repository =
      std::make_shared<channel::adapter::FileChannelConfigRepository>(
          config.ChannelConfigPath());
  auto radio = std::make_shared<channel::adapter::ConsoleRadioDevice>();

  auto set_channel_use_case =
      std::make_shared<channel::application::SetChannelUseCase>(repository,
                                                                radio);
  auto get_channel_use_case =
      std::make_shared<channel::application::GetChannelUseCase>(repository);
  auto reconcile_channel_use_case =
      std::make_shared<channel::application::ReconcileChannelUseCase>(
          repository, radio);

  if (!repository->Load().desired.has_value()) {
    set_channel_use_case->Execute(config.DefaultChannel());
  } else {
    reconcile_channel_use_case->Execute();
  }

  return channel::api::ChannelApi(set_channel_use_case, get_channel_use_case,
                                  reconcile_channel_use_case);
}

}  // namespace gateway::bootstrap
