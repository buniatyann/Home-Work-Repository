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
 * @brief Computes the Gini index for a split dataset.
 * @tparam T Numeric data type
 * @param groups Pair of split datasets (left and right)
 * @param classes Set of unique class labels
 * @return Gini index value indicating impurity (lower is better)
 */
template<typename T>
T gini_index(const std::pair<dataset_t<T>, dataset_t<T>>& groups, const std::set<T>& classes) {
    T total_size = static_cast<T>(groups.first.size() + groups.second.size());
    T gini = 0;

    for (const auto& group : {groups.first, groups.second}) {
        size_t size = group.size();
        if (size == 0) continue;

        T score = 0;
        for (T class_val : classes) {
            size_t count = std::count_if(group.begin(), group.end(),
                [class_val](const std::vector<T>& row) {
                    return row.back() == class_val;
                });
            T p = static_cast<T>(count) / static_cast<T>(size);
            score += p * p;
        }

        gini += (1 - score) * (static_cast<T>(size) / total_size);
    }

    return gini;
}

