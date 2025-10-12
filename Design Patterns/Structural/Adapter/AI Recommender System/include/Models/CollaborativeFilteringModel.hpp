#ifndef COLLABORATIVEFILTERINGMODEL_HPP
#define COLLABORATIVEFILTERINGMODEL_HPP

#include "../Interface/ICollaborativeFiltering.hpp"

class CollaborativeFilteringModel : public ICollaborativeFiltering {
public:
    void train(const std::vector<std::vector<double>>& userItemMatrix) override;
    std::vector<std::string> recommend(unsigned userId, unsigned topN) override;

private:
    std::vector<std::vector<double>> userItemMatrix_;
    double computeSimilarity(unsigned user1, unsigned user2);
};

#endif // COLLABORATIVEFILTERINGMODEL_HPP