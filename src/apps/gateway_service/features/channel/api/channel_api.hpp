#pragma once

#include <memory>
#include <string>

#include "get_channel_use_case.hpp"
#include "reconcile_channel_use_case.hpp"
#include "set_channel_use_case.hpp"

namespace gateway::channel::api {

class ChannelApi {
 public:
  ChannelApi(
      std::shared_ptr<application::SetChannelUseCase> set_channel_use_case,
      std::shared_ptr<application::GetChannelUseCase> get_channel_use_case,
      std::shared_ptr<application::ReconcileChannelUseCase>
          reconcile_channel_use_case);

  void SetChannel(int channel);
  int GetChannel();
  std::string GetChannelMessage();
  bool ReconcileChannel();

 private:
  std::shared_ptr<application::SetChannelUseCase> set_channel_use_case_;
  std::shared_ptr<application::GetChannelUseCase> get_channel_use_case_;
  std::shared_ptr<application::ReconcileChannelUseCase>
      reconcile_channel_use_case_;
};

}  // namespace gateway::channel::api
