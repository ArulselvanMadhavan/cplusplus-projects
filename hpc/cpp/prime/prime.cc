#include "cxxopts.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  cxxopts::Options options("prime", "prime numbers");
  options.add_options()("n,number", "Number to check for prime",
                        cxxopts::value<int>()->default_value("2"));
  options.add_options()("d,divisor", "Number to divide",
                        cxxopts::value<int>()->default_value("1"));
  auto result = options.parse(argc, argv);
  auto n = result["number"].as<int>();
  auto d = result["divisor"].as<int>();
  n = n % d;
  std::cout << "Modulus result:" << n << '\n';
  return 0;
}
