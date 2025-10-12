#ifndef CONTENT_BASED_FILTERING_ADAPTER_H
#define CONTENT_BASED_FILTERING_ADAPTER_H

#include "../Interface/IRecommender.hpp"
#include "../Models/ContentBasedFilteringModel.hpp"
#include <memory>

class ContentBasedFilteringAdapter : public IRecommender {
public:
    explicit ContentBasedFilteringAdapter(std::unique_ptr<ContentBasedFilteringModel> model);
    std::vector<std::string> recommend(unsigned int userId, unsigned int topN) override;

private:
    std::unique_ptr<ContentBasedFilteringModel> model_;
};

#endif // CONTENT_BASED_FILTERING_ADAPTER_H