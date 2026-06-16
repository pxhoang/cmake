#pragma once

#include <stdexcept>

namespace gateway::device::domain {

class DeviceId {
 public:
  explicit DeviceId(int value) : value_(value) {
    if (value < 1 || value > 255) {
      throw std::invalid_argument("invalid_device_id");
    }
  }

  int Value() const { return value_; }

 private:
  int value_;
};

inline bool operator==(const DeviceId& left, const DeviceId& right) {
  return left.Value() == right.Value();
}

}  // namespace gateway::device::domain
