#include "cxxopts.hpp"
#include <iostream>
#include <math.h>
#include <stdlib.h>

bool check_divisor(int n, int d) {
  auto result = (n % d) == 0;
  return result;
}

int find_factors(int n, int d) {
  while (d > 1) {
    auto is_divisible = check_divisor(n, d);
    if (is_divisible) {
      break;
    } else {
      d = d - 1;
    }
  }
  return d;
}

int main(int argc, char *argv[]) {
  cxxopts::Options options("prime", "prime numbers");
  options.add_options()("n,number", "Number to check for prime",
                        cxxopts::value<int>()->default_value("2"));
  auto result = options.parse(argc, argv);
  auto n = result["number"].as<int>();

  auto d = std::sqrt(n);
  d = std::ceil(d);
  int factor0 = find_factors(n, d);
  std::cout << factor0 << "|" << n / factor0 << '\n';
}
