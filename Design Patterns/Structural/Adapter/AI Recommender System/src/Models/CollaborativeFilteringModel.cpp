#include "../../include/Models/CollaborativeFilteringModel.hpp"
#include <cmath>
#include <algorithm>

void CollaborativeFilteringModel::train(const std::vector<std::vector<double>>& userItemMatrix) {
    userItemMatrix_ = userItemMatrix;
}

double CollaborativeFilteringModel::computeSimilarity(unsigned int user1, unsigned int user2) {
    double dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (size_t i = 0; i < userItemMatrix_[user1].size(); ++i) {
        dotProduct += userItemMatrix_[user1][i] * userItemMatrix_[user2][i];
        norm1 += userItemMatrix_[user1][i] * userItemMatrix_[user1][i];
        norm2 += userItemMatrix_[user2][i] * userItemMatrix_[user2][i];
    }
    
    norm1 = std::sqrt(norm1);
    norm2 = std::sqrt(norm2);
    
    return (norm1 > 0 && norm2 > 0) ? dotProduct / (norm1 * norm2) : 0.0;
}

std::vector<std::string> CollaborativeFilteringModel::recommend(unsigned int userId, unsigned int topN) {
    std::vector<std::pair<double, unsigned int>> similarities;
    for (size_t i = 0; i < userItemMatrix_.size(); ++i) {
        if (static_cast<unsigned int>(i) != userId) {
            double sim = computeSimilarity(userId, i);
            similarities.emplace_back(sim, i);
        }
    }

    std::sort(similarities.rbegin(), similarities.rend());
    std::vector<std::string> recommendations;
    for (const auto& [sim, otherUser] : similarities) {
        for (size_t item = 0; item < userItemMatrix_[otherUser].size(); ++item) {
            if (userItemMatrix_[userId][item] == 0 && userItemMatrix_[otherUser][item] > 0) {
                recommendations.push_back("Item" + std::to_string(item));
                if (recommendations.size() >= topN) {
                    return recommendations;
                }
            }
        }
    }
    
    return recommendations;
}