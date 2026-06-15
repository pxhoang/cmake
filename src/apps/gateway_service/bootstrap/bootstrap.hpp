#pragma once

#include "app_config.hpp"
#include "channel_api.hpp"

namespace gateway::bootstrap {

class Bootstrap {
 public:
  channel::api::ChannelApi createChannelApi(
      const infrastructure::AppConfig& config);
};

}  // namespace gateway::bootstrap
