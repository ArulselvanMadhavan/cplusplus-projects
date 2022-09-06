#include "neural_net.h"
#include <iomanip>
#include <iostream>
#include <torch/cuda.h>
#include <torch/torch.h>

int main() {
  std::cout << "FFNN\n";

  // Device
  auto cuda_available = torch::cuda::is_available();
  torch::Device device(cuda_available ? torch::kCUDA : torch::kCPU);

  const int64_t isize = 784;
  const int64_t hsize = 500;
  const int64_t num_classes = 10;
  const int64_t bsize = 100;
  const size_t num_epochs = 5;
  const double lr = 0.001;

  const std::string data_path = "../data/mnist";

  auto train_ds = torch::data::datasets::MNIST(data_path)
                      .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
                      .map(torch::data::transforms::Stack<>());

  auto num_train_samples = train_ds.size().value();

  auto test_ds = torch::data::datasets::MNIST(
                     data_path, torch::data::datasets::MNIST::Mode::kTest)
                     .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
                     .map(torch::data::transforms::Stack<>());

  auto num_test_samples = test_ds.size().value();

  // Dataloaders
  auto train_loader =
      torch::data::make_data_loader<torch::data::samplers::RandomSampler>(
          std::move(train_ds), bsize);
  auto test_loader =
      torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
          std::move(test_ds), bsize);

  // Neural Network model
  NeuralNet model(isize, hsize, num_classes);
  model->to(device);

  // Optimizer
  torch::optim::SGD optimizer(model->parameters(),
                              torch::optim::SGDOptions(lr));

  // Set floating point output precision
  std::cout << std::fixed << std::setprecision(4);

  for (size_t epoch = 0; epoch != num_epochs; ++epoch) {
    double running_loss = 0.0;
    size_t num_correct = 0;

    for (auto &batch : *train_loader) {
      auto data = batch.data.view({bsize, -1}).to(device);
      auto target = batch.target.to(device);

      auto output = model->forward(data);
      auto loss = torch::nn::functional::cross_entropy(output, target);

      running_loss += loss.item<double>() * data.size(0);

      auto prediction = output.argmax(1);

      num_correct += prediction.eq(target).sum().item<int64_t>();

      optimizer.zero_grad();
      loss.backward();
      optimizer.step();
    }

    auto sample_mean_loss = running_loss / num_train_samples;
    auto accuracy = static_cast<double>(num_correct) / num_train_samples;

    std::cout << "Epoch [" << (epoch + 1) << "/" << num_epochs
              << "], Trainset - Loss: " << sample_mean_loss
              << ", Accuracy: " << accuracy << '\n';
  }

  std::cout << "Training finished\n";
  std::cout << "Testing...\n";

  // Test the model
  model->eval();
  torch::NoGradGuard no_grad;

  double running_loss = 0.0;
  size_t num_correct = 0;
  for (const auto &batch : *test_loader) {
    auto data = batch.data.view({bsize, -1}).to(device);
    auto target = batch.target.to(device);

    auto output = model->forward(data);

    auto loss = torch::nn::functional::cross_entropy(output, target);
    running_loss += loss.item<double>() * data.size(0);
    auto prediction = output.argmax(1);
    num_correct += prediction.eq(target).sum().item<int64_t>();
  }

  std::cout << "Testing finished\n";
  auto test_acc = static_cast<double>(num_correct) / num_test_samples;
  auto test_sample_mean_loss = running_loss / num_test_samples;

  std::cout << "Testset - Loss: " << test_sample_mean_loss
            << ", Accuracy: " << test_acc << '\n';
}
