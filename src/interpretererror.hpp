#pragma once

#include <exception>
#include <string>

class interpreterError : public std::runtime_error {
  public:
  interpreterError(const std::string &msg)
      : std::runtime_error(msg) {}
};
