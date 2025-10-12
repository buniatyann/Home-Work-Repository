#include "../../include/Utils/EvaluationMetrics.hpp"
#include <cmath>

double EvaluationMetrics::computeRmse(const std::vector<double>& actual, const std::vector<double>& predicted) {
    if (actual.size() != predicted.size()) {
        return 0.0;
    }
    
    double mse = 0.0;
    for (size_t i = 0; i < actual.size(); ++i) {
        mse += std::pow(actual[i] - predicted[i], 2);
    }
    
    return std::sqrt(mse / actual.size());
}