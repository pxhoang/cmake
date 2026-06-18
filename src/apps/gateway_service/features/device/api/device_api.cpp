#include "device_api.hpp"

#include <utility>

#include "protocol/text_format.hpp"

namespace gateway_service {

DeviceApi::DeviceApi(std::shared_ptr<DeviceService> device_service)
    : device_service_(std::move(device_service)) {}

void DeviceApi::SelectDevice(int device_id) {
  device_service_->SelectDevice(device_id);
}

int DeviceApi::GetSelectedDevice() {
  return device_service_->GetSelectedDevice().Value();
}

std::string DeviceApi::GetSelectedDeviceMessage() {
  return protocol::FormatDeviceMessage(GetSelectedDevice());
}

bool DeviceApi::ReconcileDevice() {
  return device_service_->ReconcileDevice();
}

}  // namespace gateway_service
