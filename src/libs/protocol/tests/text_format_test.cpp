#include "protocol/text_format.hpp"

#include <gtest/gtest.h>

TEST(TextFormatTest, FormatsChannelMessage) {
  EXPECT_EQ(protocol::formatChannelMessage(15), "Current channel: 15");
}
