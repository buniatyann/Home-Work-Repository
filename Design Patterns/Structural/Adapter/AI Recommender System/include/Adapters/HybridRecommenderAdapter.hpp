#ifndef HYBRID_RECOMMENDER_ADAPTER_H
#define HYBRID_RECOMMENDER_ADAPTER_H

#include "../Interface/IRecommender.hpp"
#include "../Models/HybridRecommenderModel.hpp"
#include <memory>

class HybridRecommenderAdapter : public IRecommender {
public:
    explicit HybridRecommenderAdapter(std::unique_ptr<HybridRecommenderModel> model);
    std::vector<std::string> recommend(unsigned int userId, unsigned int topN) override;

private:
    std::unique_ptr<HybridRecommenderModel> model_;
};

#endif // HYBRID_RECOMMENDER_ADAPTER_H