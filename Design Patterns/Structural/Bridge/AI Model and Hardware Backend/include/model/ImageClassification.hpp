#ifndef IMAGE_CLASSIFICATION_HPP
#define IMAGE_CLASSIFICATION_HPP

#include "../interface/INeuralNet.hpp"
#include <iostream>

class ImageClassification : public INeuralNet {
public:
    ~ImageClassification() override = default;

    void run() override {
        std::cout << "Image Classification is running" << std::endl;
    }

    void info() override {
        std::cout << "Image Classification Generator" << std::endl;
    }

    void train() override {
        std::cout << "Image Classification Generator is training" << std::endl;
    }
};

#endif // IMAGE_CLASSIFICATION_HPP
