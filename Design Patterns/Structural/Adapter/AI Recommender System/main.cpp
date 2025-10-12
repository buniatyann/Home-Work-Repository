#include "include/Services/RecommenderService.hpp"
#include "include/Adapters/CollaborativeFilteringAdapter.hpp"
#include "include/Adapters/HybridRecommenderAdapter.hpp"
#include "include/Adapters/ContentBasedFilteringAdapter.hpp"
#include "include/Models/CollaborativeFilteringModel.hpp"
#include "include/Models/ContentBasedFilteringModel.hpp"
#include "include/Models/HybridRecommenderModel.hpp"
#include "include/Utils/DataPreprocessing.hpp"
#include <iostream>

int main() {
    std::vector<std::vector<double>> userItemMatrix = {
        {5, 3, 0, 1},
        {4, 0, 0, 1},
        {1, 1, 0, 5},
        {0, 0, 5, 4}
    };

    std::vector<std::string> items = {"Item0", "Item1", "Item2", "Item3"};
    auto normalizedRatings = DataPreprocessing::normalizeRatings(userItemMatrix);
    auto itemFeatures = DataPreprocessing::extractFeatures(items);

    auto cfModel = std::make_unique<CollaborativeFilteringModel>();
    cfModel->train(normalizedRatings);
    auto cfAdapter = std::make_unique<CollaborativeFilteringAdapter>(cfModel.get());
    RecommenderService cfService(std::move(cfAdapter));
    auto cfRecs = cfService.getRecommendations(0, 2);
    std::cout << "Collaborative Filtering Recommendations for User 0:\n";
    for (const auto& rec : cfRecs) {
        std::cout << rec << "\n";
    }

    auto cbModel = std::make_unique<ContentBasedFilteringModel>();
    cbModel->train(itemFeatures);
    auto cbAdapter = std::make_unique<ContentBasedFilteringAdapter>(cbModel.get());
    RecommenderService cbService(std::move(cbAdapter));
    auto cbRecs = cbService.getRecommendations(0, 2);
    std::cout << "\nContent-Based Filtering Recommendations for User 0:\n";
    for (const auto& rec : cbRecs) {
        std::cout << rec << "\n";
    }

    auto hybridModel = std::make_unique<HybridRecommenderModel>();
    hybridModel->setCollaborativeWeight(0.6);
    hybridModel->setContentBasedWeight(0.4);
    auto hybridAdapter = std::make_unique<HybridRecommenderAdapter>(hybridModel.get());
    RecommenderService hybridService(std::move(hybridAdapter));
    auto hybridRecs = hybridService.getRecommendations(0, 2);
    std::cout << "\nHybrid Recommendations for User 0:\n";
    for (const auto& rec : hybridRecs) {
        std::cout << rec << "\n";
    }

    return 0;
}