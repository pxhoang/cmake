#include "bootstrap.hpp"

#include <memory>

#include "console_device_controller.hpp"
#include "file_device_state_repository.hpp"
#include "get_selected_device_use_case.hpp"
#include "reconcile_device_use_case.hpp"
#include "select_device_use_case.hpp"

namespace gateway::bootstrap {

device::api::DeviceApi Bootstrap::CreateDeviceApi(
    const infrastructure::AppConfig& config) {
  auto repository =
      std::make_shared<device::persistence::FileDeviceStateRepository>(
          config.DeviceStatePath());
  auto controller =
      std::make_shared<device::adapter::ConsoleDeviceController>();

  auto select_device_use_case =
      std::make_shared<device::application::SelectDeviceUseCase>(repository,
                                                                 controller);
  auto get_selected_device_use_case =
      std::make_shared<device::application::GetSelectedDeviceUseCase>(
          repository);
  auto reconcile_device_use_case =
      std::make_shared<device::application::ReconcileDeviceUseCase>(repository,
                                                                    controller);

  if (!repository->Load().desired.has_value()) {
    select_device_use_case->Execute(config.DefaultDeviceId());
  } else {
    reconcile_device_use_case->Execute();
  }

  return device::api::DeviceApi(select_device_use_case,
                                get_selected_device_use_case,
                                reconcile_device_use_case);
}

}  // namespace gateway::bootstrap
