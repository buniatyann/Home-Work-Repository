#include <vector>
#include <set>
#include <limits>
#include <type_traits>
#include <algorithm>

/**
 * @brief Alias for the dataset type. Each row is a vector of values, with the last value being the class label.
 * @tparam T Numeric data type (e.g., int, float, double)
 */
template<typename T>
using dataset_t = std::vector<std::vector<T>>;

/**
 * @brief Structure representing the result of a dataset split.
 * @tparam T Numeric data type
 */
template<typename T>
struct split_t {
    int index;  ///< Feature index on which the split is made
    T value;    ///< Feature value used to split
    std::pair<dataset_t<T>, dataset_t<T>> groups; ///< Resulting left and right groups after the split
};

/**
 * @brief Splits a dataset into two groups based on a given feature index and threshold value.
 * @tparam T Numeric data type
 * @param index Index of the feature used for splitting
 * @param value Threshold value for the split
 * @param dataset Input dataset
 * @return A pair of datasets: left group (< value), right group (>= value)
 */
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
std::pair<dataset_t<T>, dataset_t<T>> test_split(int index, T value, const dataset_t<T>& dataset) {
    dataset_t<T> left, right;
    for (const auto& row : dataset) {
        if (row[index] < value) {
            left.push_back(row);
        }
        else {
            right.push_back(row);
        }
    }
   
    return {left, right};
}

/**
 * @brief Finds the best feature index and value to split the dataset based on minimum Gini index.
 * @tparam T Numeric data type
 * @param dataset Input dataset to split
 * @return A split_t struct containing the best index, value, and split groups
 */
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
split_t<T> get_split(const dataset_t<T>& dataset) {
    std::set<T> class_values;
    for (const auto& row : dataset) {
        class_values.insert(row.back());
    }

    int best_index = -1;
    T best_value = T();
    T best_score = std::numeric_limits<T>::max();
    std::pair<dataset_t<T>, dataset_t<T>> best_groups;

    int n_features = static_cast<int>(dataset[0].size()) - 1;

    for (int index = 0; index < n_features; ++index) {
        for (const auto& row : dataset) {
            auto groups = test_split<T>(index, row[index], dataset);
            T gini = gini_index(groups, class_values);
            if (gini < best_score) {
                best_index = index;
                best_value = row[index];
                best_score = gini;
                best_groups = groups;
            }
        }
    }

    return {best_index, best_value, best_groups};
}
