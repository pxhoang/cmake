#include "bootstrap.hpp"

#include <functional>
#include <memory>
#include <utility>

#include "console_device_controller.hpp"
#include "default_device_service.hpp"
#include "file_device_state_repository.hpp"
#include "get_selected_device_service.hpp"
#include "initialize_device_service.hpp"
#include "reconcile_device_service.hpp"
#include "select_device_service.hpp"

namespace gateway_service {

GatewayComposition::GatewayComposition(DeviceApi device_api,
                                       std::function<void(int)> initialize_device)
    : device_api_(std::move(device_api)),
      initialize_device_(std::move(initialize_device)) {}

void GatewayComposition::Initialize(const AppConfig& config) {
  initialize_device_(config.DefaultDeviceId());
}

DeviceApi& GatewayComposition::Device() { return device_api_; }

GatewayComposition Bootstrap::Create(const AppConfig& config) {
  auto repository =
      std::make_shared<FileDeviceStateRepository>(config.DeviceStatePath());
  auto controller = std::make_shared<ConsoleDeviceController>();

  auto select_device_service =
      std::make_shared<SelectDeviceService>(repository, controller);
  auto get_selected_device_service =
      std::make_shared<GetSelectedDeviceService>(repository);
  auto reconcile_device_service =
      std::make_shared<ReconcileDeviceService>(repository, controller);
  auto initialize_device_service = std::make_shared<InitializeDeviceService>(
      repository, select_device_service, reconcile_device_service);
  auto device_service = std::make_shared<DefaultDeviceService>(
      select_device_service, get_selected_device_service,
      reconcile_device_service);

  return GatewayComposition(
      DeviceApi(device_service),
      [initialize_device_service](int default_device_id) {
        initialize_device_service->Execute(default_device_id);
      });
}

}  // namespace gateway_service
