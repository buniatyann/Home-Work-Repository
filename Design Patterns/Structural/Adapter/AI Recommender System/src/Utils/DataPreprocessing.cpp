#include "../../include/Utils/DataPreprocessing.hpp"

std::vector<std::vector<double>> DataPreprocessing::normalizeRatings(const std::vector<std::vector<double>>& ratings) {
    std::vector<std::vector<double>> normalized = ratings;
    for (auto& userRatings : normalized) {
        double mean = 0.0;
        double count = 0.0;
        for (double rating : userRatings) {
            if (rating > 0.0) {
                mean += rating;
                count += 1.0;
            }
        }

        mean = count > 0.0 ? mean / count : 0.0;
        for (double& rating : userRatings) {
            if (rating > 0) {
                rating -= mean;
            }
        }
    }

    return normalized;
}

std::vector<std::vector<double>> DataPreprocessing::extractFeatures(const std::vector<std::string>& items) {
    std::vector<std::vector<double>> features(items.size(), std::vector<double>(10, 0.0));
    for (std::size_t i = 0; i < items.size(); ++i) {
        features[i][i % 10] = 1.0;
    }

    return features;
}