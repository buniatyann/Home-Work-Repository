#include <vector>
#include <string>
#include <unordered_map>
#include <set>

// Leetcode 2353 needs to be reviwed

class FoodRatings {
public:
    FoodRatings(const std::vector<std::string>& foods, const std::vector<std::string>& cuisines, const std::vector<int>& ratings) {
        for (int i = 0; i < foods.size(); ++i) {
            food_to_cuisine_rating[foods[i]] = {cuisines[i], ratings[i]};
            cuisine_to_foods[cuisines[i]].emplace(-ratings[i], foods[i]);
        }
    }
    
    void changeRating(const std::string& food, int newRating) {
        auto& [cuisine, oldRating] = food_to_cuisine_rating[food];
        cuisine_to_foods[cuisine].erase({-oldRating, food});
        oldRating = newRating;
        cuisine_to_foods[cuisine].emplace(-newRating, food);
    }
    
    std::string highestRated(const std::string& cuisine) {
        return cuisine_to_foods[cuisine].begin()->second;
    }

private:
    std::unordered_map<std::string, std::pair<std::string, int>> food_to_cuisine_rating;
    std::unordered_map<std::string, std::set<std::pair<int, std::string>>> cuisine_to_foods;
};