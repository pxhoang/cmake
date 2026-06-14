#pragma once

#include <stdexcept>

class WirelessChannel {
public:
    explicit WirelessChannel(int value) : value_(value) {
        if (value < 11 || value > 26) {
            throw std::invalid_argument("invalid_wireless_channel");
        }
    }

    int value() const {
        return value_;
    }

private:
    int value_;
};
