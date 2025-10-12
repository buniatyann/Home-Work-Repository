#ifndef IRECOMMENDER_HPP
#define IRECOMMENDER_HPP

#include <string>
#include <vector>

class IRecommender {
public:
    virtual ~IRecommender() = default;
    virtual std::vector<std::string> recommend(unsigned user_id, unsigned top_n) = 0;
};

#endif // IRECOMMENDER_HPP