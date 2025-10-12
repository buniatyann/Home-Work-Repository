#include "../../include/Models/HybridRecommenderModel.hpp"
#include <algorithm>

HybridRecommenderModel::HybridRecommenderModel() {}

void HybridRecommenderModel::setCollaborativeWeight(double weight) {
    cfWeight_ = weight;
}

void HybridRecommenderModel::setContentBasedWeight(double weight) {
    cbWeight_ = weight;
}

std::vector<std::string> HybridRecommenderModel::recommend(unsigned int userId, unsigned int topN) {
    auto cfRecs = cfModel_.recommend(userId, topN * 2);
    auto cbRecs = cbModel_.recommend(userId, topN * 2);

    std::vector<std::pair<std::string, double>> combinedScores;
    for (const auto& item : cfRecs) {
        combinedScores.emplace_back(item, cfWeight_);
    }
    for (const auto& item : cbRecs) {
        auto it = std::find_if(combinedScores.begin(), combinedScores.end(),
            [&item](const auto& p) { return p.first == item; });
        if (it != combinedScores.end()) {
            it->second += cbWeight_;
        } 
        else {
            combinedScores.emplace_back(item, cbWeight_);
        }
    }

    std::sort(combinedScores.rbegin(), combinedScores.rend(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    std::vector<std::string> recommendations;
    for (const auto& [item, score] : combinedScores) {
        recommendations.push_back(item);
        if (recommendations.size() >= topN) {
            break;
        }
    }
 
    return recommendations;
}