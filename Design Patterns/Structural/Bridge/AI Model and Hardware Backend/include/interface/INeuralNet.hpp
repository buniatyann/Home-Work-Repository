#ifndef I_NEURAL_NET_HPP
#define I_NEURAL_NET_HPP

class INeuralNet {
public:
    virtual ~INeuralNet() = default;
    virtual void run() = 0;
    virtual void info() = 0;
    virtual void train() = 0;
};

#endif // I_NEURAL_NET_HPP
