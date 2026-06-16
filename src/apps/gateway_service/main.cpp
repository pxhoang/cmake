#include <chrono>
#include <csignal>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <thread>

#include "app_config.hpp"
#include "bootstrap.hpp"

namespace {

volatile std::sig_atomic_t stop_requested = 0;

void RequestStop(int) { stop_requested = 1; }

void PrintCurrentChannel(gateway::channel::api::ChannelApi& api) {
  std::cout << api.GetChannelMessage() << std::endl;
}

int RunOnce(gateway::channel::api::ChannelApi& api) {
  PrintCurrentChannel(api);
  return 0;
}

int Serve(gateway::channel::api::ChannelApi& api,
          const gateway::infrastructure::AppConfig& config) {
  std::signal(SIGINT, RequestStop);
  std::signal(SIGTERM, RequestStop);

  PrintCurrentChannel(api);

  const auto interval =
      std::chrono::milliseconds(config.ReconcileIntervalMilliseconds());

  while (stop_requested == 0) {
    std::this_thread::sleep_for(interval);

    if (stop_requested == 0) {
      api.ReconcileChannel();
    }
  }

  return 0;
}

}  // namespace

int main(int argc, char* argv[]) {
  try {
    const std::string_view command = argc > 1 ? argv[1] : "once";

    if (command != "once" && command != "serve") {
      throw std::runtime_error("usage: gateway_service [once|serve]");
    }

    const auto config = gateway::infrastructure::AppConfig::Load();
    gateway::bootstrap::Bootstrap bootstrap;
    auto api = bootstrap.CreateChannelApi(config);

    if (command == "serve") {
      return Serve(api, config);
    }

    return RunOnce(api);
  } catch (const std::exception& ex) {
    std::cerr << "fatal_error: " << ex.what() << "\n";
    return 1;
  }
}
