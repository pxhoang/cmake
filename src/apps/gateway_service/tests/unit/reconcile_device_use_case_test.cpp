#include "reconcile_device_use_case.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <optional>

namespace {

using gateway::device::application::DeviceController;
using gateway::device::application::DeviceStateRepository;
using gateway::device::application::ReconcileDeviceUseCase;
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

TEST(ReconcileDeviceUseCaseTest, AppliesDesiredDeviceWhenStateDiffers) {
  auto repository = std::make_shared<FakeRepository>();
  repository->state.desired = DeviceId(20);
  repository->state.applied = DeviceId(15);
  auto controller = std::make_shared<FakeController>();
  ReconcileDeviceUseCase useCase(repository, controller);

  EXPECT_TRUE(useCase.Execute());

  ASSERT_TRUE(controller->applied_device_id.has_value());
  EXPECT_EQ(controller->applied_device_id->Value(), 20);
  ASSERT_TRUE(repository->state.applied.has_value());
  EXPECT_EQ(repository->state.applied->Value(), 20);
}

TEST(ReconcileDeviceUseCaseTest, DoesNothingWhenStateAlreadyMatches) {
  auto repository = std::make_shared<FakeRepository>();
  repository->state.desired = DeviceId(15);
  repository->state.applied = DeviceId(15);
  auto controller = std::make_shared<FakeController>();
  ReconcileDeviceUseCase useCase(repository, controller);

  EXPECT_FALSE(useCase.Execute());
  EXPECT_FALSE(controller->applied_device_id.has_value());
}

}  // namespace
