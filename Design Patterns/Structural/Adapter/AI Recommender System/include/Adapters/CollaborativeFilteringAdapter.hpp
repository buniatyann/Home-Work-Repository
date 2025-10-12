#ifndef COLLABORATIVE_FILTERING_ADAPTER_H
#define COLLABORATIVE_FILTERING_ADAPTER_H

#include "../Interface/IRecommender.hpp"
#include "../Models/CollaborativeFilteringModel.hpp"
#include <memory>

class CollaborativeFilteringAdapter : public IRecommender {
public:
    explicit CollaborativeFilteringAdapter(std::unique_ptr<CollaborativeFilteringModel> model);
    std::vector<std::string> recommend(unsigned int userId, unsigned int topN) override;

private:
    std::unique_ptr<CollaborativeFilteringModel> model_;
};

#endif // COLLABORATIVE_FILTERING_ADAPTER_H