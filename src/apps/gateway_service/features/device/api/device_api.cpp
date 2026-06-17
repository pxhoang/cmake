#include "device_api.hpp"

#include <utility>

#include "protocol/text_format.hpp"

namespace gateway_service {

DeviceApi::DeviceApi(
    std::shared_ptr<SelectDeviceUseCase> select_device_use_case,
    std::shared_ptr<GetSelectedDeviceUseCase> get_selected_device_use_case,
    std::shared_ptr<ReconcileDeviceUseCase> reconcile_device_use_case)
    : select_device_use_case_(std::move(select_device_use_case)),
      get_selected_device_use_case_(std::move(get_selected_device_use_case)),
      reconcile_device_use_case_(std::move(reconcile_device_use_case)) {}

void DeviceApi::SelectDevice(int device_id) {
  select_device_use_case_->Execute(device_id);
}

int DeviceApi::GetSelectedDevice() {
  return get_selected_device_use_case_->Execute().Value();
}

std::string DeviceApi::GetSelectedDeviceMessage() {
  return protocol::FormatDeviceMessage(GetSelectedDevice());
}

bool DeviceApi::ReconcileDevice() {
  return reconcile_device_use_case_->Execute();
}

}  // namespace gateway_service
