#include "select_device_service.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

namespace {

using gateway_service::DeviceController;
using gateway_service::DeviceId;
using gateway_service::DeviceState;
using gateway_service::DeviceStateRepository;
using gateway_service::SelectDeviceService;

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

TEST(SelectDeviceServiceTest, PersistsDesiredAndAppliedDevice) {
  auto repository = std::make_shared<FakeRepository>();
  auto controller = std::make_shared<FakeController>();
  SelectDeviceService service(repository, controller);

  service.Execute(15);

  ASSERT_TRUE(repository->state.desired.has_value());
  EXPECT_EQ(repository->state.desired->Value(), 15);
  ASSERT_TRUE(repository->state.applied.has_value());
  EXPECT_EQ(repository->state.applied->Value(), 15);
  ASSERT_TRUE(controller->applied_device_id.has_value());
  EXPECT_EQ(controller->applied_device_id->Value(), 15);
}

TEST(SelectDeviceServiceTest, PreservesDesiredStateWhenDeviceApplyFails) {
  auto repository = std::make_shared<FakeRepository>();
  auto controller = std::make_shared<FakeController>();
  controller->fail = true;
  SelectDeviceService service(repository, controller);

  EXPECT_THROW(service.Execute(20), std::runtime_error);

  ASSERT_TRUE(repository->state.desired.has_value());
  EXPECT_EQ(repository->state.desired->Value(), 20);
  EXPECT_FALSE(repository->state.applied.has_value());
}

}  // namespace
