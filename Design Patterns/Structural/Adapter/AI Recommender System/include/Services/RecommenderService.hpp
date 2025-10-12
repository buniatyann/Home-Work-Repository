#ifndef RECOMMENDER_SERVICE_H
#define RECOMMENDER_SERVICE_H

#include "../Interface/IRecommender.hpp"
#include <memory>

class RecommenderService {
public:
    explicit RecommenderService(std::unique_ptr<IRecommender> recommender);
    std::vector<std::string> getRecommendations(unsigned int userId, unsigned int topN);

private:
    std::unique_ptr<IRecommender> recommender_;
};

#endif // RECOMMENDER_SERVICE_H