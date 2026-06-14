#include "protocol/text_format.hpp"

namespace protocol {

std::string formatChannelMessage(int channel) {
    return "Current channel: " + std::to_string(channel);
}

}  // namespace protocol
