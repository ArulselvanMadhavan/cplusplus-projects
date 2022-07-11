#pragma once

#include <string>

namespace hello_object {
class HelloObject {
public:
  HelloObject(const std::string &name) : name_{name} {}
  void greet() const;

private:
  const std::string name_;
};
} // namespace hello_object
