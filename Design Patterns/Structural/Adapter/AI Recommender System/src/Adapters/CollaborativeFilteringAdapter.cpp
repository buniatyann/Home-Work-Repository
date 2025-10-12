#include "../../include/Adapters/CollaborativeFilteringAdapter.hpp"

CollaborativeFilteringAdapter::CollaborativeFilteringAdapter(std::unique_ptr<CollaborativeFilteringModel> model)
    : model_(std::move(model)) {}

std::vector<std::string> CollaborativeFilteringAdapter::recommend(unsigned int userId, unsigned int topN) {
    return model_->recommend(userId, topN);
}