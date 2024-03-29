#include <CL/sycl.hpp>
#include <iostream>
using namespace sycl;

const std::string secret{};

const auto sz = secret.size();

int main() {
  queue Q;

  char* result = malloc_shared<char>(sz, Q);
  std::memcpy(result, secret.data(), sz);

  Q.parallel_for(sz,[=](auto&i){
		      result[i] -=1;
		    }).wait();

  std::cout << result << "\n";
  return 0;
}
