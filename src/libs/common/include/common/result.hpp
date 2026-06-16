#pragma once

#include <string>
#include <utility>

namespace common {

struct Result {
  bool success;
  std::string message;

  static Result Ok(std::string message = "ok") {
    return Result{true, std::move(message)};
  }

  static Result Error(std::string message) {
    return Result{false, std::move(message)};
  }
};

}  // namespace common
