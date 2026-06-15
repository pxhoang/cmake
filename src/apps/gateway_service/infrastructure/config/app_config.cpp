#include "app_config.hpp"

#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <utility>

#include "wireless_channel.hpp"

namespace gateway::infrastructure {
namespace {

std::string readString(const char* name, std::string defaultValue) {
  const char* value = std::getenv(name);

  if (value == nullptr) {
    return defaultValue;
  }

  if (*value == '\0') {
    throw std::runtime_error(std::string(name) + "_must_not_be_empty");
  }

  return value;
}

int readInteger(const char* name, int defaultValue) {
  const char* value = std::getenv(name);

  if (value == nullptr) {
    return defaultValue;
  }

  std::size_t parsedCharacters = 0;
  long parsedValue = 0;

  try {
    parsedValue = std::stol(value, &parsedCharacters);
  } catch (const std::exception&) {
    throw std::runtime_error(std::string(name) + "_must_be_an_integer");
  }

  if (parsedCharacters != std::string_view(value).size() ||
      parsedValue < std::numeric_limits<int>::min() ||
      parsedValue > std::numeric_limits<int>::max()) {
    throw std::runtime_error(std::string(name) + "_must_be_an_integer");
  }

  return static_cast<int>(parsedValue);
}

}  // namespace

AppConfig::AppConfig(std::string channelConfigPath, int defaultChannel,
                     int reconcileIntervalMilliseconds)
    : channelConfigPath_(std::move(channelConfigPath)),
      defaultChannel_(defaultChannel),
      reconcileIntervalMilliseconds_(reconcileIntervalMilliseconds) {}

AppConfig AppConfig::load() {
  auto channelConfigPath = readString(
      "CHANNEL_CONFIG_PATH", ".img/runtime/gateway_service/channel.state");
  const int defaultChannel = readInteger("DEFAULT_CHANNEL", 15);
  const int reconcileIntervalMilliseconds =
      readInteger("RECONCILE_INTERVAL_MS", 5000);

  const channel::domain::WirelessChannel validatedDefaultChannel{
      defaultChannel};
  static_cast<void>(validatedDefaultChannel);

  if (reconcileIntervalMilliseconds <= 0) {
    throw std::runtime_error("RECONCILE_INTERVAL_MS_must_be_positive");
  }

  return AppConfig(std::move(channelConfigPath), defaultChannel,
                   reconcileIntervalMilliseconds);
}

const std::string& AppConfig::channelConfigPath() const {
  return channelConfigPath_;
}

int AppConfig::defaultChannel() const { return defaultChannel_; }

int AppConfig::reconcileIntervalMilliseconds() const {
  return reconcileIntervalMilliseconds_;
}

}  // namespace gateway::infrastructure
