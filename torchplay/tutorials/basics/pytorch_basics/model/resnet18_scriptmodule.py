import torch
import torchvision

def main():
    model = torchvision.models.resnet18(pretrained=True)

    for param in model.parameters():
        param.requires_grad = False

    model.fc = torch.nn.Linear(model.fc.in_features, 100)
    example = torch.rand(1,3,224,224)

    traced_script_module = torch.jit.trace(model, example)
    filename = "resnet18_scriptmodule.pt"
    traced_script_module.save(filename)
    print(f"Successfully created scriptmodule file {filename}.")

if __name__ == "__main__":
    main()
