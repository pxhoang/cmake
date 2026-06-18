#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

#include <cerrno>
#include <chrono>
#include <csignal>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <system_error>
#include <string_view>

#include "app_config.hpp"
#include "bootstrap.hpp"

namespace {

volatile std::sig_atomic_t stop_requested = 0;
int stop_signal_pipe[2] = {-1, -1};

void RequestStop(int) {
  stop_requested = 1;

  if (stop_signal_pipe[1] >= 0) {
    const char byte = 's';
    const auto ignored = ::write(stop_signal_pipe[1], &byte, 1);
    static_cast<void>(ignored);
  }
}

void SetNonBlocking(int descriptor) {
  const int flags = ::fcntl(descriptor, F_GETFL, 0);

  if (flags < 0 ||
      ::fcntl(descriptor, F_SETFL, flags | O_NONBLOCK) < 0) {
    throw std::system_error(errno, std::generic_category(),
                            "signal_pipe_nonblocking_failed");
  }
}

void DrainStopSignalPipe() {
  char buffer[64];

  while (::read(stop_signal_pipe[0], buffer, sizeof(buffer)) > 0) {
  }
}

class StopSignal {
 public:
  StopSignal() {
    stop_requested = 0;

    if (::pipe(stop_signal_pipe) != 0) {
      throw std::system_error(errno, std::generic_category(),
                              "signal_pipe_create_failed");
    }

    SetNonBlocking(stop_signal_pipe[0]);
    SetNonBlocking(stop_signal_pipe[1]);

    previous_interrupt_handler_ = std::signal(SIGINT, RequestStop);
    previous_terminate_handler_ = std::signal(SIGTERM, RequestStop);

    if (previous_interrupt_handler_ == SIG_ERR ||
        previous_terminate_handler_ == SIG_ERR) {
      throw std::system_error(errno, std::generic_category(),
                              "signal_handler_install_failed");
    }
  }

  StopSignal(const StopSignal&) = delete;
  StopSignal& operator=(const StopSignal&) = delete;

  ~StopSignal() {
    std::signal(SIGINT, previous_interrupt_handler_);
    std::signal(SIGTERM, previous_terminate_handler_);

    if (stop_signal_pipe[0] >= 0) {
      ::close(stop_signal_pipe[0]);
    }

    if (stop_signal_pipe[1] >= 0) {
      ::close(stop_signal_pipe[1]);
    }

    stop_signal_pipe[0] = -1;
    stop_signal_pipe[1] = -1;
  }

  bool WaitForStop(std::chrono::milliseconds timeout) {
    pollfd descriptor{stop_signal_pipe[0], POLLIN, 0};
    const auto timeout_count = timeout.count();
    const int poll_timeout =
        timeout_count > std::numeric_limits<int>::max()
            ? std::numeric_limits<int>::max()
            : static_cast<int>(timeout_count);

    const int result = ::poll(&descriptor, 1, poll_timeout);

    if (result == 0) {
      return stop_requested != 0;
    }

    if (result < 0) {
      if (errno == EINTR) {
        return stop_requested != 0;
      }

      throw std::system_error(errno, std::generic_category(),
                              "signal_pipe_poll_failed");
    }

    DrainStopSignalPipe();
    return true;
  }

 private:
  using SignalHandler = void (*)(int);

  SignalHandler previous_interrupt_handler_ = SIG_DFL;
  SignalHandler previous_terminate_handler_ = SIG_DFL;
};

void PrintCurrentDevice(gateway_service::DeviceApi& api) {
  std::cout << api.GetSelectedDeviceMessage() << std::endl;
}

int RunOnce(gateway_service::DeviceApi& api) {
  PrintCurrentDevice(api);
  return 0;
}

int Serve(gateway_service::DeviceApi& api,
          const gateway_service::AppConfig& config) {
  StopSignal stop_signal;

  PrintCurrentDevice(api);

  const auto interval =
      std::chrono::milliseconds(config.ReconcileIntervalMilliseconds());

  while (stop_requested == 0) {
    if (stop_signal.WaitForStop(interval)) {
      break;
    }

    api.ReconcileDevice();
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

    const auto config = gateway_service::AppConfig::Load();
    gateway_service::Bootstrap bootstrap;
    auto composition = bootstrap.Create(config);
    composition.Initialize(config);
    auto& api = composition.Device();

    if (command == "serve") {
      return Serve(api, config);
    }

    return RunOnce(api);
  } catch (const std::exception& ex) {
    std::cerr << "fatal_error: " << ex.what() << "\n";
    return 1;
  }
}
