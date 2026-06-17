#include "bootstrap.hpp"

#include <memory>

#include "console_device_controller.hpp"
#include "file_device_state_repository.hpp"
#include "get_selected_device_use_case.hpp"
#include "reconcile_device_use_case.hpp"
#include "select_device_use_case.hpp"

namespace gateway_service {

DeviceApi Bootstrap::CreateDeviceApi(const AppConfig& config) {
  auto repository =
      std::make_shared<FileDeviceStateRepository>(config.DeviceStatePath());
  auto controller = std::make_shared<ConsoleDeviceController>();

  auto select_device_use_case =
      std::make_shared<SelectDeviceUseCase>(repository, controller);
  auto get_selected_device_use_case =
      std::make_shared<GetSelectedDeviceUseCase>(repository);
  auto reconcile_device_use_case =
      std::make_shared<ReconcileDeviceUseCase>(repository, controller);

  if (!repository->Load().desired.has_value()) {
    select_device_use_case->Execute(config.DefaultDeviceId());
  } else {
    reconcile_device_use_case->Execute();
  }

  return DeviceApi(select_device_use_case, get_selected_device_use_case,
                   reconcile_device_use_case);
}

}  // namespace gateway_service
