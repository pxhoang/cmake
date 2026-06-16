#include "file_device_state_repository.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <atomic>
#include <cerrno>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <system_error>
#include <utility>

namespace gateway::device::persistence {
namespace {

std::atomic<unsigned long> temporary_file_sequence{0};

std::optional<domain::DeviceId> ParseDeviceId(const std::string& value,
                                              const std::string& field) {
  if (value == "none") {
    return std::nullopt;
  }

  std::size_t parsed_characters = 0;
  int device_id = 0;

  try {
    device_id = std::stoi(value, &parsed_characters);
  } catch (const std::exception&) {
    throw std::runtime_error("device_state_invalid_" + field);
  }

  if (parsed_characters != value.size()) {
    throw std::runtime_error("device_state_invalid_" + field);
  }

  try {
    return domain::DeviceId(device_id);
  } catch (const std::invalid_argument&) {
    throw std::runtime_error("device_state_invalid_" + field);
  }
}

void SyncPath(const std::filesystem::path& path, int flags) {
  const int descriptor = ::open(path.c_str(), flags);

  if (descriptor < 0) {
    throw std::system_error(errno, std::generic_category(),
                            "device_state_sync_open_failed");
  }

  if (::fsync(descriptor) != 0) {
    const int error = errno;
    ::close(descriptor);
    throw std::system_error(error, std::generic_category(),
                            "device_state_sync_failed");
  }

  ::close(descriptor);
}

}  // namespace

FileDeviceStateRepository::FileDeviceStateRepository(std::string path)
    : path_(std::move(path)) {}

domain::DeviceState FileDeviceStateRepository::Load() {
  const std::scoped_lock lock(mutex_);
  return LoadUnlocked();
}

domain::DeviceState FileDeviceStateRepository::LoadUnlocked() {
  std::ifstream file(path_);

  if (!file) {
    if (!std::filesystem::exists(path_)) {
      return {};
    }

    throw std::runtime_error("device_state_open_failed");
  }

  std::string version_line;
  std::string desired_line;
  std::string applied_line;
  std::string extra_line;

  if (!std::getline(file, version_line) || !std::getline(file, desired_line) ||
      !std::getline(file, applied_line) || std::getline(file, extra_line)) {
    throw std::runtime_error("device_state_invalid_format");
  }

  constexpr auto desired_prefix = "desired=";
  constexpr auto applied_prefix = "applied=";

  if (version_line != "version=1" ||
      !desired_line.starts_with(desired_prefix) ||
      !applied_line.starts_with(applied_prefix)) {
    throw std::runtime_error("device_state_invalid_format");
  }

  return {
      ParseDeviceId(
          desired_line.substr(std::char_traits<char>::length(desired_prefix)),
          "desired"),
      ParseDeviceId(
          applied_line.substr(std::char_traits<char>::length(applied_prefix)),
          "applied"),
  };
}

void FileDeviceStateRepository::Save(const domain::DeviceState& state) {
  const std::scoped_lock lock(mutex_);
  const std::filesystem::path destination(path_);
  const auto parent = destination.parent_path();

  if (!parent.empty()) {
    std::filesystem::create_directories(parent);
  }

  const auto sequence =
      temporary_file_sequence.fetch_add(1, std::memory_order_relaxed);
  const auto temporary = destination.string() + ".tmp." +
                         std::to_string(::getpid()) + "." +
                         std::to_string(sequence);

  try {
    std::ofstream file(temporary, std::ios::trunc);

    if (!file) {
      throw std::runtime_error("device_state_open_failed");
    }

    const auto format_device_id =
        [](const std::optional<domain::DeviceId>& device_id) {
          return device_id.has_value() ? std::to_string(device_id->Value())
                                       : std::string("none");
        };

    file << "version=1\n"
         << "desired=" << format_device_id(state.desired) << "\n"
         << "applied=" << format_device_id(state.applied) << "\n";
    file.flush();

    if (!file) {
      throw std::runtime_error("device_state_write_failed");
    }

    file.close();
    SyncPath(temporary, O_RDONLY);
    std::filesystem::rename(temporary, destination);

    if (!parent.empty()) {
      SyncPath(parent, O_RDONLY | O_DIRECTORY);
    }
  } catch (...) {
    std::error_code ignored;
    std::filesystem::remove(temporary, ignored);
    throw;
  }
}

}  // namespace gateway::device::persistence
