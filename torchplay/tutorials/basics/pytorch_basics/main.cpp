#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <iomanip>

void print_script_module(const torch::jit::script::Module& module, size_t spaces = 0) {
  for(const auto& sub_module : module.named_children()) {
    if(!sub_module.name.empty()) {
      std::cout << std::string(spaces, ' ') << sub_module.value.type()->name().value().name()
                << " " << sub_module.name << '\n';
    }
    print_script_module(sub_module.value, spaces + 2);
  }
}

int main(){
  std::cout << "Pytorch basics\n\n";
  std::cout << std::fixed << std::setprecision(4);
  std::cout << "Basic autograd example\n";
  // Create Tensors
  torch::Tensor x = torch::tensor(1.0, torch::requires_grad());
  torch::Tensor w = torch::tensor(2.0, torch::requires_grad());
  torch::Tensor b = torch::tensor(3.0, torch::requires_grad());

  // Comp graph
  auto y = w * x + b;

  // gradients
  y.backward();

  std::cout << x.grad() << '\n';
  std::cout << w.grad() << '\n';
  std::cout << b.grad() << '\n';

  std::cout << "Basic autograd example 2\n";
  x = torch::randn({10,3});
  y = torch::randn({10,2});

  torch::nn::Linear linear(3,2);
  std::cout << "w:\n" << linear->weight << '\n';
  std::cout << "b:\n" << linear->bias << '\n';

  torch::nn::MSELoss criterion;
  torch::optim::SGD optimizer(linear->parameters(),torch::optim::SGDOptions(0.01));

  auto pred = linear->forward(x);
  auto loss = criterion(pred, y);
  std::cout << "Loss: " << loss.item<double>() << '\n';

  loss.backward();

  std::cout << "dL/dW:\n" << linear->weight.grad() << '\n';
  std::cout << "dL/db:\n" << linear->bias.grad() << '\n';

  optimizer.step();

  pred = linear->forward(x);
  loss = criterion(pred, y);
  std::cout << "Loss after 1 optimization step: " << loss.item<double>() << '\n';

  std::cout << "Creating tensors from existing data\n";
  float data_array[] = {1,2,3,4};
  torch::Tensor t1 = torch::from_blob(data_array, {2,2});
  std::cout << "Tensor from array:\n" << t1 << '\n';

  TORCH_CHECK(data_array == t1.data_ptr<float>());

  // tensor from vector
  std::vector<float> data_vector = {1,2,3,4};
  torch::Tensor t2 = torch::from_blob(data_vector.data(), {2,2});
  std::cout << "Tensor from vector:\n" << t2 << "\n\n";

  TORCH_CHECK(data_vector.data() == t2.data_ptr<float>());

  std::cout << "Slicing and extracting parts from tensors\n";

  std::vector<int64_t> test_data = {1,2,3,4,5,6,7,8,9};
  torch::Tensor s = torch::from_blob(test_data.data(), {3,3}, torch::kInt64);
  std::cout << "s:\n" << s << '\n';

  using torch::indexing::Slice;
  using torch::indexing::None;
  using torch::indexing::Ellipsis;

  std::cout << "\"s[0,2]\" as tensor:\n" << s.index({0,2}) << '\n';
  std::cout << "\"s[0,2]\" as value:\n" << s.index({0,2}).item<int64_t>() << '\n';

  std::cout << "\"s[:,2]\":\n" << s.index({Slice(), 2}) << '\n';
  std::cout << "\"s[:2,:]\":\n" << s.index({Slice(None,2), Slice()}) << '\n';

  std::cout << "\"s[:,1:]\":\n" << s.index({Slice(), Slice(1, None)}) << '\n';
  std::cout << "\"s[:,::2]\":\n" << s.index({Slice(), Slice(None, None, 2)}) << '\n';
  std::cout << "\"s[:2,1]\":\n" << s.index({Slice(None,2),1}) << '\n';
  std::cout << "\"s[...,:2]\":\n" << s.index({Ellipsis, Slice(None, 2)}) << '\n';

  std::cout << "Input pipeline\n";
  const std::string MNIST_data_path = "../data/mnist";

  auto dataset = torch::data::datasets::MNIST(MNIST_data_path)
    .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
    .map(torch::data::transforms::Stack<>());

  auto example = dataset.get_batch(0);
  std::cout << "Sample data size: ";
  std::cout << example.data.sizes() << "\n";
  std::cout << "Sample target: " << example.target.item<int>() << '\n';

  auto dataloader = torch::data::make_data_loader<torch::data::samplers::RandomSampler>(dataset, 64);

  auto example_batch = *dataloader->begin();
  std::cout << "Sample batch - data size: ";
  std::cout << example_batch.data.sizes() << "\n";
  std::cout << "Sample batch - target size: ";
  std::cout << example_batch.target.sizes() << '\n';

  const std::string pretrained_model_path = "../tutorials/basics/pytorch_basics/model/resnet18_scriptmodule.pt";
  torch::jit::script::Module resnet;

  try {
    resnet = torch::jit::load(pretrained_model_path);
  }
  catch (const torch::Error& error) {
    std::cerr << "Could not load scriptmodule from file " << pretrained_model_path << '\n';
    return -1;
  }

  const auto fc_weight = resnet.attr("fc").toModule().attr("weight").toTensor();
  auto in_features = fc_weight.size(1);
  auto out_features = fc_weight.size(0);

  std::cout << "FC layer: in_features=" << in_features << ", out_features=" << out_features << "\n";

  auto sample_input = torch::randn({1,3,224,224});
  std::vector<torch::jit::IValue> inputs{sample_input};

  // Fwd pass
  std::cout << "I/p size: ";
  std::cout << sample_input.sizes() << "\n";
  auto output = resnet.forward(inputs).toTensor();
  std::cout << "Output size: ";
  std::cout << output.sizes() << '\n';

  // save and load
  std::cout << "Save and load\n";

  // Simple example model
  torch::nn::Sequential model{
    torch::nn::Conv2d(torch::nn::Conv2dOptions(1,16,3).stride(2).padding(1)),
    torch::nn::ReLU()
  };

  // model output
  const std::string model_save_path = "output/model.pt";

  torch::save(model, model_save_path);

  std::cout << "Saved model:\n" << model << '\n';

  torch::load(model, model_save_path);

  std::cout << "Loaded model:\n" << model;

  std::cout << "---Resnet18---" << '\n';
  print_script_module(resnet ,2);
}
