#pragma once

#include <memory>
#include <string>

#include "get_channel_use_case.hpp"
#include "reconcile_channel_use_case.hpp"
#include "set_channel_use_case.hpp"

namespace gateway::channel::api {

class ChannelApi {
 public:
  ChannelApi(std::shared_ptr<application::SetChannelUseCase> setChannelUseCase,
             std::shared_ptr<application::GetChannelUseCase> getChannelUseCase,
             std::shared_ptr<application::ReconcileChannelUseCase>
                 reconcileChannelUseCase);

  void setChannel(int channel);
  int getChannel();
  std::string getChannelMessage();
  bool reconcileChannel();

 private:
  std::shared_ptr<application::SetChannelUseCase> setChannelUseCase_;
  std::shared_ptr<application::GetChannelUseCase> getChannelUseCase_;
  std::shared_ptr<application::ReconcileChannelUseCase>
      reconcileChannelUseCase_;
};

}  // namespace gateway::channel::api
