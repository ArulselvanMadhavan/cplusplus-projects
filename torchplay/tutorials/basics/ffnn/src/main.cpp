#include <iostream>
#include <torch/cuda.h>
#include <torch/torch.h>

int main() {
  std::cout << "FFNN\n";

  // Device
  auto cuda_available = torch::cuda::is_available();
  std::cout << cuda_available << std::endl;
}
