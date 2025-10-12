#ifndef HYBRIDRECOMMENDER_HPP
#define HYBRIDRECOMMENDER_HPP

#include "IRecommender.hpp"

class IHybridRecommender : public IRecommender {
public:
    virtual void setCollaborativeWeight(double weight) = 0;
    virtual void setContentBasedWeight(double weight) = 0;
};

#endif // HYBRIDRECOMMENDER_HPP