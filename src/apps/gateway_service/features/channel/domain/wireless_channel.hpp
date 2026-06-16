#pragma once

#include <stdexcept>

namespace gateway::channel::domain {

class WirelessChannel {
 public:
  explicit WirelessChannel(int value) : value_(value) {
    if (value < 11 || value > 26) {
      throw std::invalid_argument("invalid_wireless_channel");
    }
  }

  int Value() const { return value_; }

 private:
  int value_;
};

inline bool operator==(const WirelessChannel& left,
                       const WirelessChannel& right) {
  return left.Value() == right.Value();
}

}  // namespace gateway::channel::domain
