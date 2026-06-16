#include "app_config.hpp"

#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <utility>

#include "wireless_channel.hpp"

namespace gateway::infrastructure {
namespace {

std::string ReadString(const char* name, std::string default_value) {
  const char* value = std::getenv(name);

  if (value == nullptr) {
    return default_value;
  }

  if (*value == '\0') {
    throw std::runtime_error(std::string(name) + "_must_not_be_empty");
  }

  return value;
}

int ReadInteger(const char* name, int default_value) {
  const char* value = std::getenv(name);

  if (value == nullptr) {
    return default_value;
  }

  std::size_t parsed_characters = 0;
  long parsed_value = 0;

  try {
    parsed_value = std::stol(value, &parsed_characters);
  } catch (const std::exception&) {
    throw std::runtime_error(std::string(name) + "_must_be_an_integer");
  }

  if (parsed_characters != std::string_view(value).size() ||
      parsed_value < std::numeric_limits<int>::min() ||
      parsed_value > std::numeric_limits<int>::max()) {
    throw std::runtime_error(std::string(name) + "_must_be_an_integer");
  }

  return static_cast<int>(parsed_value);
}

}  // namespace

AppConfig::AppConfig(std::string channel_config_path, int default_channel,
                     int reconcile_interval_milliseconds)
    : channel_config_path_(std::move(channel_config_path)),
      default_channel_(default_channel),
      reconcile_interval_milliseconds_(reconcile_interval_milliseconds) {}

AppConfig AppConfig::Load() {
  auto channel_config_path = ReadString(
      "CHANNEL_CONFIG_PATH", ".img/runtime/gateway_service/channel.state");
  const int default_channel = ReadInteger("DEFAULT_CHANNEL", 15);
  const int reconcile_interval_milliseconds =
      ReadInteger("RECONCILE_INTERVAL_MS", 5000);

  const channel::domain::WirelessChannel validated_default_channel{
      default_channel};
  static_cast<void>(validated_default_channel);

  if (reconcile_interval_milliseconds <= 0) {
    throw std::runtime_error("RECONCILE_INTERVAL_MS_must_be_positive");
  }

  return AppConfig(std::move(channel_config_path), default_channel,
                   reconcile_interval_milliseconds);
}

const std::string& AppConfig::ChannelConfigPath() const {
  return channel_config_path_;
}

int AppConfig::DefaultChannel() const { return default_channel_; }

int AppConfig::ReconcileIntervalMilliseconds() const {
  return reconcile_interval_milliseconds_;
}

}  // namespace gateway::infrastructure
