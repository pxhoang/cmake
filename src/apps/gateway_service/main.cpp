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

volatile std::sig_atomic_t stopRequested = 0;

void requestStop(int) { stopRequested = 1; }

void printCurrentChannel(gateway::channel::api::ChannelApi& api) {
  std::cout << api.getChannelMessage() << std::endl;
}

int runOnce(gateway::channel::api::ChannelApi& api) {
  printCurrentChannel(api);
  return 0;
}

int serve(gateway::channel::api::ChannelApi& api,
          const gateway::infrastructure::AppConfig& config) {
  std::signal(SIGINT, requestStop);
  std::signal(SIGTERM, requestStop);

  printCurrentChannel(api);

  const auto interval =
      std::chrono::milliseconds(config.reconcileIntervalMilliseconds());

  while (stopRequested == 0) {
    std::this_thread::sleep_for(interval);

    if (stopRequested == 0) {
      api.reconcileChannel();
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

    const auto config = gateway::infrastructure::AppConfig::load();
    gateway::bootstrap::Bootstrap bootstrap;
    auto api = bootstrap.createChannelApi(config);

    if (command == "serve") {
      return serve(api, config);
    }

    return runOnce(api);
  } catch (const std::exception& ex) {
    std::cerr << "fatal_error: " << ex.what() << "\n";
    return 1;
  }
}
