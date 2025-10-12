#include "../../include/Models/ContentBasedFilteringModel.hpp"
#include <cmath>
#include <algorithm>

void ContentBasedFilteringModel::train(const std::vector<std::vector<double>>& itemFeatures) {
    itemFeatures_ = itemFeatures;
    userProfiles_ = itemFeatures; // Placeholder: Aggregate item features for users
}

double ContentBasedFilteringModel::computeSimilarity(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    double dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        dotProduct += vec1[i] * vec2[i];
        norm1 += vec1[i] * vec1[i];
        norm2 += vec2[i] * vec2[i];
    }

    norm1 = std::sqrt(norm1);
    norm2 = std::sqrt(norm2);
    
    return (norm1 > 0 && norm2 > 0) ? dotProduct / (norm1 * norm2) : 0.0;
}

std::vector<std::string> ContentBasedFilteringModel::recommend(unsigned int userId, unsigned int topN) {
    std::vector<std::pair<double, unsigned int>> similarities;
    for (size_t item = 0; item < itemFeatures_.size(); ++item) {
        double sim = computeSimilarity(userProfiles_[userId], itemFeatures_[item]);
        similarities.emplace_back(sim, item);
    }
 
    std::sort(similarities.rbegin(), similarities.rend());
    std::vector<std::string> recommendations;
    for (const auto& [sim, item] : similarities) {
        recommendations.push_back("Item" + std::to_string(item));
        if (recommendations.size() >= topN) {
            break;
        }
    }
 
    return recommendations;
}