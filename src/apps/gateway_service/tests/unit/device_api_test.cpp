#include "device_api.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <optional>

namespace {

using gateway_service::DeviceApi;
using gateway_service::DeviceController;
using gateway_service::DeviceId;
using gateway_service::DeviceState;
using gateway_service::DeviceStateRepository;
using gateway_service::GetSelectedDeviceUseCase;
using gateway_service::ReconcileDeviceUseCase;
using gateway_service::SelectDeviceUseCase;

class FakeRepository final : public DeviceStateRepository {
 public:
  DeviceState Load() override { return state; }

  void Save(const DeviceState& value) override { state = value; }

  DeviceState state;
};

class FakeController final : public DeviceController {
 public:
  void ApplyDevice(const DeviceId& device_id) override {
    applied_device_id = device_id;
  }

  std::optional<DeviceId> applied_device_id;
};

TEST(DeviceApiTest, SelectsGetsAndFormatsDevice) {
  auto repository = std::make_shared<FakeRepository>();
  auto controller = std::make_shared<FakeController>();
  auto select_use_case =
      std::make_shared<SelectDeviceUseCase>(repository, controller);
  auto get_use_case = std::make_shared<GetSelectedDeviceUseCase>(repository);
  auto reconcile_use_case =
      std::make_shared<ReconcileDeviceUseCase>(repository, controller);
  DeviceApi api(select_use_case, get_use_case, reconcile_use_case);

  api.SelectDevice(20);

  EXPECT_EQ(api.GetSelectedDevice(), 20);
  EXPECT_EQ(api.GetSelectedDeviceMessage(), "Current device: 20");
  ASSERT_TRUE(controller->applied_device_id.has_value());
  EXPECT_EQ(controller->applied_device_id->Value(), 20);
}

}  // namespace
