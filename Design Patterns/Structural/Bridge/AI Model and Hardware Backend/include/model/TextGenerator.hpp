#ifndef TEXT_GENERATOR_HPP
#define TEXT_GENERATOR_HPP

#include "../interface/INeuralNet.hpp"
#include <iostream>

class TextGenerator : public INeuralNet {
public:
    ~TextGenerator() override = default;

    void run() override {
        std::cout << "Text Generator is running" << std::endl;
    }

    void info() override {
        std::cout << "Text Generator" << std::endl;
    }

    void train() override {
        std::cout << "Text Generator is training" << std::endl;
    }
};

#endif // TEXT_GENERATOR_HPP
