#include "device_api.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <optional>

namespace {

using gateway_service::DeviceService;
using gateway_service::DeviceApi;
using gateway_service::DeviceId;

class FakeDeviceService final : public DeviceService {
 public:
  void SelectDevice(int raw_device_id) override {
    selected_device_id = DeviceId(raw_device_id);
  }

  DeviceId GetSelectedDevice() override { return selected_device_id.value(); }

  bool ReconcileDevice() override {
    reconciled = true;
    return true;
  }

  std::optional<DeviceId> selected_device_id;
  bool reconciled = false;
};

TEST(DeviceApiTest, SelectsGetsAndFormatsDevice) {
  auto device_service = std::make_shared<FakeDeviceService>();
  DeviceApi api(device_service);

  api.SelectDevice(20);

  EXPECT_EQ(api.GetSelectedDevice(), 20);
  EXPECT_EQ(api.GetSelectedDeviceMessage(), "Current device: 20");
  ASSERT_TRUE(device_service->selected_device_id.has_value());
  EXPECT_EQ(device_service->selected_device_id->Value(), 20);
  EXPECT_TRUE(api.ReconcileDevice());
  EXPECT_TRUE(device_service->reconciled);
}

}  // namespace
