#include "../../include/Services/RecommenderService.hpp"

RecommenderService::RecommenderService(std::unique_ptr<IRecommender> recommender)
    : recommender_(std::move(recommender)) {}

std::vector<std::string> RecommenderService::getRecommendations(unsigned int userId, unsigned int topN) {
    return recommender_->recommend(userId, topN);
}