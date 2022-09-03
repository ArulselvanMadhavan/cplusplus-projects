#include <cstdlib>
#include <iostream>
#include "Message.hpp"

int main() {
  Message say_hello("Hello, CMake World!");
  std::cout << say_hello << std::endl;
  Message say_goodbye("Goodbye, CMake world!");
  std::cout << say_goodbye << std::endl;
  return EXIT_SUCCESS;
}
