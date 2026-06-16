#include "app_config.hpp"

#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <utility>

#include "device_id.hpp"

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

AppConfig::AppConfig(std::string device_state_path, int default_device_id,
                     int reconcile_interval_milliseconds)
    : device_state_path_(std::move(device_state_path)),
      default_device_id_(default_device_id),
      reconcile_interval_milliseconds_(reconcile_interval_milliseconds) {}

AppConfig AppConfig::Load() {
  auto device_state_path = ReadString(
      "DEVICE_STATE_PATH", ".img/runtime/gateway_service/device.state");
  const int default_device_id = ReadInteger("DEFAULT_DEVICE_ID", 1);
  const int reconcile_interval_milliseconds =
      ReadInteger("RECONCILE_INTERVAL_MS", 5000);

  const device::domain::DeviceId validated_default_device_id{default_device_id};
  static_cast<void>(validated_default_device_id);

  if (reconcile_interval_milliseconds <= 0) {
    throw std::runtime_error("RECONCILE_INTERVAL_MS_must_be_positive");
  }

  return AppConfig(std::move(device_state_path), default_device_id,
                   reconcile_interval_milliseconds);
}

const std::string& AppConfig::DeviceStatePath() const {
  return device_state_path_;
}

int AppConfig::DefaultDeviceId() const { return default_device_id_; }

int AppConfig::ReconcileIntervalMilliseconds() const {
  return reconcile_interval_milliseconds_;
}

}  // namespace gateway::infrastructure
