#include "device_api.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <optional>

namespace {

using gateway::device::api::DeviceApi;
using gateway::device::application::DeviceController;
using gateway::device::application::DeviceStateRepository;
using gateway::device::application::GetSelectedDeviceUseCase;
using gateway::device::application::ReconcileDeviceUseCase;
using gateway::device::application::SelectDeviceUseCase;
using gateway::device::domain::DeviceId;
using gateway::device::domain::DeviceState;

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
