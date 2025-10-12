#include "../../include/Adapters/HybridRecommenderAdapter.hpp"

HybridRecommenderAdapter::HybridRecommenderAdapter(std::unique_ptr<HybridRecommenderModel> model)
    : model_(std::move(model)) {}

std::vector<std::string> HybridRecommenderAdapter::recommend(unsigned int userId, unsigned int topN) {
    return model_->recommend(userId, topN);
}