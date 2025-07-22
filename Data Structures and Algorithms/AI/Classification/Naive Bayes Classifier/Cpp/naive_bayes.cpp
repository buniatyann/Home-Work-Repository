#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <type_traits>

/**
 * @brief Concept to constrain template parameter to floating point types only.
 */
template<typename T>
concept floating_point = std::is_floating_point_v<T>;

/**
 * @brief Calculates prior probabilities for each class in the dataset.
 *
 * This function computes the prior probability for each class by counting the occurrences
 * of each class label and dividing by the total number of samples. The result is a map
 * where each class label is associated with its prior probability.
 *
 * @tparam T The numeric type for probabilities (must be floating-point).
 * @param y A const reference to a vector of class labels.
 * @return An unordered_map mapping each class label to its prior probability.
 */
template<floating_point T>
std::unordered_map<std::string, T> calculate_priors(const std::vector<std::string>& y) {
    std::unordered_map<std::string, size_t> label_counts;
    label_counts.reserve(y.size() / 2);

    std::size_t total = y.size();
    for (const auto& label : y) {
        ++label_counts[label];
    }

    std::unordered_map<std::string, T> priors;
    priors.reserve(label_counts.size());
    for (const auto& [label, count] : label_counts) {
        priors[label] = static_cast<T>(count) / static_cast<T>(total);
    }

    return priors;
}

/**
 * @brief Calculates likelihood probabilities with Laplace smoothing.
 *
 * This function computes the likelihood probabilities for each feature value given each class,
 * using Laplace (add-one) smoothing to handle unseen feature values. It processes the input
 * features and class labels in a single pass to count occurrences, then applies smoothing to
 * compute probabilities. The result is a nested map structure: feature -> class -> value -> probability.
 *
 * @tparam T The numeric type for probabilities (must be floating-point).
 * @param x A const reference to a vector of feature maps, where each map contains feature name-value pairs.
 * @param y A const reference to a vector of class labels.
 * @return A nested unordered_map containing likelihood probabilities.
 */
template<floating_point T>
std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, T>>>
calculate_likelihoods(const std::vector<std::unordered_map<std::string, std::string>>& x,
                      const std::vector<std::string>& y) {
    using feature_map = std::unordered_map<std::string, std::unordered_map<std::string, size_t>>;
    std::unordered_map<std::string, feature_map> count_map;
    std::unordered_map<std::string, size_t> class_counts;
    std::unordered_set<std::string> unique_values;

    count_map.reserve(x.empty() ? 0 : x[0].size());
    class_counts.reserve(y.size() / 2);

    for (std::size_t i = 0; i < x.size(); ++i) {
        ++class_counts[y[i]];
        for (const auto& [feature, value] : x[i]) {
            ++count_map[feature][y[i]][value];
            unique_values.insert(value);
        }
    }

    std::unordered_map<std::string,
        std::unordered_map<std::string,
            std::unordered_map<std::string, T>>> likelihoods;
    
    likelihoods.reserve(count_map.size());

    std::size_t vocab_size = unique_values.size();
    for (auto& [feature, class_map] : count_map) {
        likelihoods[feature].reserve(class_map.size());
        for (auto& [class_label, value_map] : class_map) {
            std::size_t total = class_counts[class_label];
            likelihoods[feature][class_label].reserve(value_map.size());
            for (const auto& [value, count] : value_map) {
                likelihoods[feature][class_label][value] =
                    static_cast<T>(count + 1) / static_cast<T>(total + vocab_size);
            }
        }
    }

    return likelihoods;
}
