#include <gtest/gtest.h>

#include <stdexcept>

#include "device_id.hpp"

using gateway_service::DeviceId;

TEST(DeviceIdTest, StoresValidDeviceId) {
  const DeviceId device_id(15);

  EXPECT_EQ(device_id.Value(), 15);
}

TEST(DeviceIdTest, RejectsDeviceIdBelowMinimum) {
  EXPECT_THROW(DeviceId(0), std::invalid_argument);
}

TEST(DeviceIdTest, RejectsDeviceIdAboveMaximum) {
  EXPECT_THROW(DeviceId(256), std::invalid_argument);
}
