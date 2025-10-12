#ifndef CONTENT_BASED_FILTERING_MODEL_H
#define CONTENT_BASED_FILTERING_MODEL_H

#include "../Interface/IContentBasedFiltering.hpp"
#include <vector>

class ContentBasedFilteringModel : public IContentBasedFiltering {
public:
    void train(const std::vector<std::vector<double>>& itemFeatures) override;
    std::vector<std::string> recommend(unsigned int userId, unsigned int topN) override;

private:
    std::vector<std::vector<double>> itemFeatures_;
    std::vector<std::vector<double>> userProfiles_;
    double computeSimilarity(const std::vector<double>& vec1, const std::vector<double>& vec2);
};

#endif // CONTENT_BASED_FILTERING_MODEL_H