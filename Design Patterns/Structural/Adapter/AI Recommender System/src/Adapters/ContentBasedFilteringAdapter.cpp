#include "../../include/Adapters/ContentBasedFilteringAdapter.hpp"

ContentBasedFilteringAdapter::ContentBasedFilteringAdapter(std::unique_ptr<ContentBasedFilteringModel> model)
    : model_(std::move(model)) {}

std::vector<std::string> ContentBasedFilteringAdapter::recommend(unsigned int userId, unsigned int topN) {
    return model_->recommend(userId, topN);
}