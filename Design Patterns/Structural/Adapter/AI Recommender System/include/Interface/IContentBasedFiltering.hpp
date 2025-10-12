#ifndef ICONTENTBASEDFILTERING_HPP
#define ICONTENTBASEDFILTERING_HPP

#include "IRecommender.hpp"

class IContentBasedFiltering : public IRecommender {
public:
    virtual void train(const std::vector<std::vector<double>>& itemFeatures) = 0;
};

#endif // ICONTENTBASEDFILTERING_HPP