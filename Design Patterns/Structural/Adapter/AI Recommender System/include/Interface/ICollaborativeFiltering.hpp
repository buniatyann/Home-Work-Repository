#ifndef ICOLLABORATIVEFILTERING_HPP
#define ICOLLABORATIVEFILTERING_HPP

#include "IRecommender.hpp"

class ICollaborativeFiltering : public IRecommender {
public:
    virtual void train(const std::vector<std::vector<double>>& userItemMatrix) = 0;
};

#endif // ICOLLABORATIVEFILTERING_HPP