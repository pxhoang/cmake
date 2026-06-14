#include "file_channel_config_repository.hpp"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <utility>

FileChannelConfigRepository::FileChannelConfigRepository(std::string path)
    : path_(std::move(path)) {}

void FileChannelConfigRepository::save(const WirelessChannel& channel) {
    const auto parent = std::filesystem::path(path_).parent_path();

    if (!parent.empty()) {
        std::filesystem::create_directories(parent);
    }

    std::ofstream file(path_);

    if (!file) {
        throw std::runtime_error("channel_config_open_failed");
    }

    file << channel.value();
}

WirelessChannel FileChannelConfigRepository::get() {
    std::ifstream file(path_);

    if (!file) {
        throw std::runtime_error("channel_config_open_failed");
    }

    int value = 0;
    file >> value;

    return WirelessChannel(value);
}
