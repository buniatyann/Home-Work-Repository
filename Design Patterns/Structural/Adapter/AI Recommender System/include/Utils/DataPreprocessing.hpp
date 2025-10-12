#ifndef DATA_PREPROCESSING_HPP
#define DATA_PREPROCESSING_HPP

#include <vector>
#include <string>

class DataPreprocessing {
public:
    static std::vector<std::vector<double>> normalizeRatings(const std::vector<std::vector<double>>& ratings);
    static std::vector<std::vector<double>> extractFeatures(const std::vector<std::string>& items);
};

#endif // DATA_PREPROCESSING_HPP