#include "reconcile_device_service.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <optional>

namespace {

using gateway_service::DeviceController;
using gateway_service::DeviceId;
using gateway_service::DeviceState;
using gateway_service::DeviceStateRepository;
using gateway_service::ReconcileDeviceService;

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

TEST(ReconcileDeviceServiceTest, AppliesDesiredDeviceWhenStateDiffers) {
  auto repository = std::make_shared<FakeRepository>();
  repository->state.desired = DeviceId(20);
  repository->state.applied = DeviceId(15);
  auto controller = std::make_shared<FakeController>();
  ReconcileDeviceService service(repository, controller);

  EXPECT_TRUE(service.Execute());

  ASSERT_TRUE(controller->applied_device_id.has_value());
  EXPECT_EQ(controller->applied_device_id->Value(), 20);
  ASSERT_TRUE(repository->state.applied.has_value());
  EXPECT_EQ(repository->state.applied->Value(), 20);
}

TEST(ReconcileDeviceServiceTest, DoesNothingWhenStateAlreadyMatches) {
  auto repository = std::make_shared<FakeRepository>();
  repository->state.desired = DeviceId(15);
  repository->state.applied = DeviceId(15);
  auto controller = std::make_shared<FakeController>();
  ReconcileDeviceService service(repository, controller);

  EXPECT_FALSE(service.Execute());
  EXPECT_FALSE(controller->applied_device_id.has_value());
}

}  // namespace
