#include <gtest/gtest.h>

#include <stdexcept>

#include "wireless_channel.hpp"

using gateway::channel::domain::WirelessChannel;

TEST(WirelessChannelTest, StoresValidChannel) {
  const WirelessChannel channel(15);

  EXPECT_EQ(channel.value(), 15);
}

TEST(WirelessChannelTest, RejectsChannelBelowMinimum) {
  EXPECT_THROW(WirelessChannel(10), std::invalid_argument);
}

TEST(WirelessChannelTest, RejectsChannelAboveMaximum) {
  EXPECT_THROW(WirelessChannel(27), std::invalid_argument);
}
