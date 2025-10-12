#ifndef EVALUATION_METRICS_HPP
#define EVALUATION_METRICS_HPP

#include <vector>

class EvaluationMetrics {
public:
    static double computeRmse(const std::vector<double>& actual, const std::vector<double>& predicted);
};

#endif // EVALUATION_METRICS_HPP