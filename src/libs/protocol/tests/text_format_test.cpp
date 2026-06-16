#include "protocol/text_format.hpp"

#include <gtest/gtest.h>

TEST(TextFormatTest, FormatsChannelMessage) {
  EXPECT_EQ(protocol::FormatChannelMessage(15), "Current channel: 15");
}
