#pragma once

#include <string>
#include <utility>

namespace common {

struct Result {
  bool success;
  std::string message;

  static Result ok(std::string message = "ok") {
    return Result{true, std::move(message)};
  }

  static Result error(std::string message) {
    return Result{false, std::move(message)};
  }
};

}  // namespace common
