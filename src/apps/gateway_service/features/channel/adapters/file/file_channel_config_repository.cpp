#include "file_channel_config_repository.hpp"

#include <atomic>
#include <cerrno>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <system_error>
#include <utility>

#include <fcntl.h>
#include <unistd.h>

namespace gateway::channel::adapter {
namespace {

std::atomic<unsigned long> temporaryFileSequence{0};

std::optional<domain::WirelessChannel> parseChannel(
    const std::string& value,
    const std::string& field
) {
    if (value == "none") {
        return std::nullopt;
    }

    std::size_t parsedCharacters = 0;
    int channel = 0;

    try {
        channel = std::stoi(value, &parsedCharacters);
    } catch (const std::exception&) {
        throw std::runtime_error("channel_config_invalid_" + field);
    }

    if (parsedCharacters != value.size()) {
        throw std::runtime_error("channel_config_invalid_" + field);
    }

    try {
        return domain::WirelessChannel(channel);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("channel_config_invalid_" + field);
    }
}

void syncPath(const std::filesystem::path& path, int flags) {
    const int descriptor = ::open(path.c_str(), flags);

    if (descriptor < 0) {
        throw std::system_error(errno, std::generic_category(), "channel_config_sync_open_failed");
    }

    if (::fsync(descriptor) != 0) {
        const int error = errno;
        ::close(descriptor);
        throw std::system_error(error, std::generic_category(), "channel_config_sync_failed");
    }

    ::close(descriptor);
}

}  // namespace

FileChannelConfigRepository::FileChannelConfigRepository(std::string path)
    : path_(std::move(path)) {}

domain::ChannelState FileChannelConfigRepository::load() {
    const std::scoped_lock lock(mutex_);
    return loadUnlocked();
}

domain::ChannelState FileChannelConfigRepository::loadUnlocked() {
    std::ifstream file(path_);

    if (!file) {
        if (!std::filesystem::exists(path_)) {
            return {};
        }

        throw std::runtime_error("channel_config_open_failed");
    }

    std::string versionLine;
    std::string desiredLine;
    std::string appliedLine;
    std::string extraLine;

    if (!std::getline(file, versionLine) || !std::getline(file, desiredLine) ||
        !std::getline(file, appliedLine) || std::getline(file, extraLine)) {
        throw std::runtime_error("channel_config_invalid_format");
    }

    constexpr auto desiredPrefix = "desired=";
    constexpr auto appliedPrefix = "applied=";

    if (versionLine != "version=1" || !desiredLine.starts_with(desiredPrefix) ||
        !appliedLine.starts_with(appliedPrefix)) {
        throw std::runtime_error("channel_config_invalid_format");
    }

    return {
        parseChannel(desiredLine.substr(std::char_traits<char>::length(desiredPrefix)), "desired"),
        parseChannel(appliedLine.substr(std::char_traits<char>::length(appliedPrefix)), "applied"),
    };
}

void FileChannelConfigRepository::save(const domain::ChannelState& state) {
    const std::scoped_lock lock(mutex_);
    const std::filesystem::path destination(path_);
    const auto parent = destination.parent_path();

    if (!parent.empty()) {
        std::filesystem::create_directories(parent);
    }

    const auto sequence = temporaryFileSequence.fetch_add(1, std::memory_order_relaxed);
    const auto temporary =
        destination.string() + ".tmp." + std::to_string(::getpid()) + "." + std::to_string(sequence);

    try {
        std::ofstream file(temporary, std::ios::trunc);

        if (!file) {
            throw std::runtime_error("channel_config_open_failed");
        }

        const auto formatChannel = [](const std::optional<domain::WirelessChannel>& channel) {
            return channel.has_value() ? std::to_string(channel->value()) : std::string("none");
        };

        file << "version=1\n"
             << "desired=" << formatChannel(state.desired) << "\n"
             << "applied=" << formatChannel(state.applied) << "\n";
        file.flush();

        if (!file) {
            throw std::runtime_error("channel_config_write_failed");
        }

        file.close();
        syncPath(temporary, O_RDONLY);
        std::filesystem::rename(temporary, destination);

        if (!parent.empty()) {
            syncPath(parent, O_RDONLY | O_DIRECTORY);
        }
    } catch (...) {
        std::error_code ignored;
        std::filesystem::remove(temporary, ignored);
        throw;
    }
}

}  // namespace gateway::channel::adapter
