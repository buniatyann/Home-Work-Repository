#include <vector>
#include <tuple>
#include <stdexcept>
#include <random>
#include <limits>

using dataset_t = const std::vector<std::pair<std::vector<float>, float>>; 
using return_t = std::tuple<std::vector<float>, float>;

float dot_product(const std::vector<float>& a, const std::vector<float>& b) {
    if (a.size() != b.size()) {
        throw std::runtime_error("dot_product: vectors must be of the same length");
    }
    
    float result = 0.0f;
    for (std::size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    
    return result;
}

double mean_squared_error(const dataset_t& dataset, const std::vector<float>& theta,float theta_0) {
    if (dataset.empty()) {
        throw std::runtime_error("mean_squared_error: dataset must be non-empty");
    }
    if (dataset[0].first.size() != theta.size()) {
        throw std::runtime_error("mean_squared_error: dataset and theta must have the same dimensionality");
    }

    std::size_t n = dataset.size();
    double error = 0.0;

    for (const auto& [features, label] : dataset) {
        float prediction = dot_product(features, theta) + theta_0;
        float diff = prediction - label;
        error += diff * diff;
    }

    return error / n;
}

double test_error(const dataset_t& dataset,const std::vector<float>& theta, float theta_0) {
    return mean_squared_error(dataset, theta, theta_0); // for now, use same metric
}

return_t random_linear_classifier(const dataset_t& dataset,std::size_t k_trials) {
    std::size_t dim = dataset[0].first.size();
    std::default_random_engine rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    std::vector<float> best_theta;
    float best_theta_0 = 0.0f;
    double min_error = std::numeric_limits<double>::max();

    for (std::size_t k = 0; k < k_trials; ++k) {
        std::vector<float> theta(dim);
        for (float& t : theta) 
            t = dist(rng);
        float theta_0 = dist(rng);

        double error = mean_squared_error(dataset, theta, theta_0);
        if (error < min_error) {
            min_error = error;
            best_theta = theta;
            best_theta_0 = theta_0;
        }
    }

    return {best_theta, best_theta_0};
}

return_t cross_validate(const dataset_t& dataset, std::size_t k_trials) {
    return random_linear_classifier(dataset, k_trials);
}
