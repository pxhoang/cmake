#include "protocol/text_format.hpp"

#include <gtest/gtest.h>

TEST(TextFormatTest, FormatsDeviceMessage) {
  EXPECT_EQ(protocol::FormatDeviceMessage(15), "Current device: 15");
}
