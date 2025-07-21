#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <map>
#include <algorithm>
#include <functional>
#include <type_traits>

// === Type Aliases ===
template <typename T>
using feature_vector = std::vector<T>;

template <typename T>
using labeled_point = std::pair<feature_vector<T>, std::string>;

template <typename T>
using dataset = std::vector<labeled_point<T>>;

using distance_label_pair = std::pair<double, std::string>;

// === Function Definitions ===

/**
 * @brief Compute the Euclidean distance between two points.
 * @tparam T Numeric type (int, float, double, etc.)
 * @param point1 First point (vector of T)
 * @param point2 Second point (vector of T)
 * @return Euclidean distance as double
 */
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
double euclidean_distance(const feature_vector<T>& point1, const feature_vector<T>& point2) {
    if (point1.size() != point2.size()) {
        throw std::invalid_argument("euclidean_distance: vectors must have the same size");
    }

    double sum = 0;
    for (std::size_t i = 0; i < point1.size(); ++i) {
        sum += std::pow(static_cast<double>(point1[i] - point2[i]), 2);
    }

    return std::sqrt(sum);
}

/**
 * @brief Perform k-Nearest Neighbors classification.
 * @tparam T Numeric type for feature values (int, float, double, etc.)
 * @param data Vector of labeled data points: (features, class label)
 * @param query The query feature vector to classify
 * @param k Number of neighbors to consider
 * @param distance_fn Function to compute distance between vectors
 * @return The predicted class label
 * @throws std::invalid_argument on invalid input or size mismatch
 */
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
std::string k_nearest_neighbors(const dataset<T>& data, const feature_vector<T>& query, std::size_t k,
    const std::function<double(const feature_vector<T>&, const feature_vector<T>&)>& distance_fn) 
{
    if (data.empty()) {
        throw std::invalid_argument("k_nearest_neighbors: dataset is empty");
    }
    if (k == 0) {
        throw std::invalid_argument("k_nearest_neighbors: k must be greater than 0");
    }
    if (query.size() != data[0].first.size()) {
        throw std::invalid_argument("k_nearest_neighbors: query size does not match data feature size");
    }

    std::vector<distance_label_pair> distances;
    try {
        for (const auto& entry : data) {
            double distance = distance_fn(entry.first, query);
            distances.emplace_back(distance, entry.second);
        }
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Distance computation failed: ") + e.what());
    }

    std::sort(distances.begin(), distances.end());

    std::map<std::string, int> label_count;
    for (std::size_t i = 0; i < std::min(k, distances.size()); ++i) {
        ++label_count[distances[i].second];
    }

    std::string majority_label;
    std::size_t max_count = 0;
    for (const auto& pair : label_count) {
        if (pair.second > max_count) {
            max_count = pair.second;
            majority_label = pair.first;
        }
    }

    return majority_label;
}
