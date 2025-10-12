#ifndef HYBRID_RECOMMENDER_MODEL_H
#define HYBRID_RECOMMENDER_MODEL_H

#include "../Interface/IHybridRecommender.hpp"
#include "CollaborativeFilteringModel.hpp"
#include "ContentBasedFilteringModel.hpp"

class HybridRecommenderModel : public IHybridRecommender {
public:
    HybridRecommenderModel();
    void setCollaborativeWeight(double weight) override;
    void setContentBasedWeight(double weight) override;
    std::vector<std::string> recommend(unsigned int userId, unsigned int topN) override;

private:
    CollaborativeFilteringModel cfModel_;
    ContentBasedFilteringModel cbModel_;
    double cfWeight_ = 0.5;
    double cbWeight_ = 0.5;
};

#endif // HYBRID_RECOMMENDER_MODEL_H