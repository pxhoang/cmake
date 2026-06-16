#include "protocol/text_format.hpp"

namespace protocol {

std::string FormatDeviceMessage(int device_id) {
  return "Current device: " + std::to_string(device_id);
}

}  // namespace protocol
