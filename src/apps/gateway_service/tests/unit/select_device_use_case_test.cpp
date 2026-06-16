#include "select_device_use_case.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

namespace {

using gateway::device::application::DeviceController;
using gateway::device::application::DeviceStateRepository;
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
    if (fail) {
      throw std::runtime_error("device_apply_failed");
    }

    applied_device_id = device_id;
  }

  bool fail = false;
  std::optional<DeviceId> applied_device_id;
};

TEST(SelectDeviceUseCaseTest, PersistsDesiredAndAppliedDevice) {
  auto repository = std::make_shared<FakeRepository>();
  auto controller = std::make_shared<FakeController>();
  SelectDeviceUseCase useCase(repository, controller);

  useCase.Execute(15);

  ASSERT_TRUE(repository->state.desired.has_value());
  EXPECT_EQ(repository->state.desired->Value(), 15);
  ASSERT_TRUE(repository->state.applied.has_value());
  EXPECT_EQ(repository->state.applied->Value(), 15);
  ASSERT_TRUE(controller->applied_device_id.has_value());
  EXPECT_EQ(controller->applied_device_id->Value(), 15);
}

TEST(SelectDeviceUseCaseTest, PreservesDesiredStateWhenDeviceApplyFails) {
  auto repository = std::make_shared<FakeRepository>();
  auto controller = std::make_shared<FakeController>();
  controller->fail = true;
  SelectDeviceUseCase useCase(repository, controller);

  EXPECT_THROW(useCase.Execute(20), std::runtime_error);

  ASSERT_TRUE(repository->state.desired.has_value());
  EXPECT_EQ(repository->state.desired->Value(), 20);
  EXPECT_FALSE(repository->state.applied.has_value());
}

}  // namespace
