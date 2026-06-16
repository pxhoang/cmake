#include "protocol/text_format.hpp"

namespace protocol {

std::string FormatChannelMessage(int channel) {
  return "Current channel: " + std::to_string(channel);
}

}  // namespace protocol
