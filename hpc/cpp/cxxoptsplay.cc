// bear -- g++ -o cxxoptsplay.o cxxoptsplay.cc --std=c++17
// -I/home/arul/dev/cppsources/cxxopts/include/
#include "cxxopts.hpp"
#include <iostream>
#include <vector>
int main(int argc, char *argv[]) {
  cxxopts::Options options("programname", "Program description");
  options.add_options()("n,ntimes", "number of times",
                        cxxopts::value<int>()->default_value("37"));
  options.add_options()(
      "a,array", "array of values",
      cxxopts::value<std::vector<int>>()->default_value("1,2,3"));
  auto result = options.parse(argc, argv);
  auto number_of_times = result["ntimes"].as<int>();
  std::cout << number_of_times << '\n';
  auto array = result["array"].as<std::vector<int>>();
  for (auto a : array)
    std::cout << a << ",";
  std::cout << '\n';
  return 0;
}
