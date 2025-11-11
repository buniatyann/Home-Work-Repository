#include <iostream>
#include <memory>

#include "../include/interface/IHardwareBackend.hpp"
#include "../include/interface/INeuralNet.hpp"

#include "../include/backend/CPUBackend.hpp"
#include "../include/backend/GPUBackend.hpp"
#include "../include/backend/TPUBackend.hpp"

#include "../include/model/GraphModel.hpp"
#include "../include/model/ImageClassification.hpp"
#include "../include/model/TextGenerator.hpp"

#include "../include/AI Platform/AIModel.hpp"

int main() {
    auto cpu = std::make_shared<CPUBackend>("CPU-0");
    auto gpu = std::make_shared<GPUBackend>("GPU-1");
    auto tpu = std::make_shared<TPUBackend>("TPU-2");

    auto graphModel = std::make_shared<GraphModel>();
    auto imageModel = std::make_shared<ImageClassification>();
    auto textModel = std::make_shared<TextGenerator>();

    AIModel model(cpu, imageModel);

    std::cout << "\n=== Initial Configuration ===" << std::endl;
    model.showInfo();
    model.load("ImageNet_v2");
    model.runInference();
    model.trainModel();

    std::cout << "\n=== Switching to GPU ===" << std::endl;
    model.setBackend(gpu);
    model.load("ImageNet_v3");
    model.runInference();

    std::cout << "\n=== Switching Model to Text Generator ===" << std::endl;
    model.setNetwork(textModel);
    model.load("GPT-Mini");
    model.showInfo();
    model.trainModel();
    model.runInference();

    std::cout << "\n=== Switching to TPU ===" << std::endl;
    model.setBackend(tpu);
    model.load("GraphNet_Pro");
    model.setNetwork(graphModel);
    model.showInfo();
    model.trainModel();
    model.runInference();

    std::cout << "\n=== End of Demo ===" << std::endl;
    return 0;
}
