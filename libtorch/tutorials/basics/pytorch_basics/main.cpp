#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <iomanip>

int main() {
  std::cout << "Pytorch Basics rocks \n";
  std::cout << std::fixed << std::setprecision(4);

  // Autograd
  std::cout << "Autograd ex:1 \n";
  torch::Tensor x = torch::tensor(1.0, torch::requires_grad());
  torch::Tensor w = torch::tensor(2.0, torch::requires_grad());
  torch::Tensor b = torch::tensor(3.0, torch::requires_grad());

  auto y = w * x + b;
  y.backward();

  std::cout << x.grad() << '\n';
  std::cout << w.grad() << '\n';
  std::cout << b.grad() << "\n\n";
}
