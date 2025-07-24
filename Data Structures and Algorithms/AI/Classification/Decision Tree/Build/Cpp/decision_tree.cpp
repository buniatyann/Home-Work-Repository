#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <limits>
#include <memory>

template<typename T>
using dataset_t = std::vector<std::vector<T>>;

/**
 * @brief Structure representing a decision node or terminal leaf in the tree.
 */
template<typename T>
struct node_t {
    int index = -1;
    T value = T();
    T terminal_value = T();
    bool is_terminal = false;
    std::unique_ptr<node_t<T>> left = nullptr;
    std::unique_ptr<node_t<T>> right = nullptr;
};

/**
 * @brief Create a terminal node with the most common class value in the group.
 * @param group A subset of the dataset.
 * @return The most frequent class label in the group.
 */
template<typename T>
T create_terminal(const dataset_t<T>& group) {
    std::map<T, int> frequency;
    for (const auto& row : group) {
        frequency[row.back()]++;
    }

    T majority_class = group[0].back();
    int max_count = 0;
    for (const auto& entry : frequency) {
        if (entry.second > max_count) {
            max_count = entry.second;
            majority_class = entry.first;
        }
    }
    
    return majority_class;
}

/**
 * @brief Recursively splits the dataset and builds the decision tree.
 * @param node Pointer to the current node in the tree.
 * @param max_depth The maximum depth the tree is allowed to grow.
 * @param min_size The minimum number of samples in a node to allow splitting.
 * @param depth The current depth of the node.
 */
template<typename T>
void recurse_split(std::unique_ptr<node_t<T>>& node, int max_depth, int min_size, int depth) {
    auto groups = test_split<T>(node->index, node->value, dataset_t<T>());
    // Replace above with: node must carry groups from get_split or pass explicitly.

    dataset_t<T> left_group = groups.first;
    dataset_t<T> right_group = groups.second;

    if (left_group.empty() || right_group.empty()) {
        T terminal = create_terminal<T>(left_group.empty() ? right_group : left_group);
        node->left = std::make_unique<node_t<T>>();
        node->right = std::make_unique<node_t<T>>();
        node->left->terminal_value = terminal;
        node->right->terminal_value = terminal;
        node->left->is_terminal = node->right->is_terminal = true;
        return;
    }

    if (depth >= max_depth) {
        node->left = std::make_unique<node_t<T>>();
        node->right = std::make_unique<node_t<T>>();
        node->left->terminal_value = create_terminal(left_group);
        node->right->terminal_value = create_terminal(right_group);
        node->left->is_terminal = node->right->is_terminal = true;
        return;
    }

    if (static_cast<int>(left_group.size()) <= min_size) {
        node->left = std::make_unique<node_t<T>>();
        node->left->terminal_value = create_terminal(left_group);
        node->left->is_terminal = true;
    } 
    else {
        auto split = get_split<T>(left_group);
        node->left = std::make_unique<node_t<T>>();
        node->left->index = split.index;
        node->left->value = split.value;
        recurse_split<T>(node->left, max_depth, min_size, depth + 1);
    }

    if (static_cast<int>(right_group.size()) <= min_size) {
        node->right = std::make_unique<node_t<T>>();
        node->right->terminal_value = create_terminal(right_group);
        node->right->is_terminal = true;
    } 
    else {
        auto split = get_split<T>(right_group);
        node->right = std::make_unique<node_t<T>>();
        node->right->index = split.index;
        node->right->value = split.value;
        recurse_split<T>(node->right, max_depth, min_size, depth + 1);
    }
}

/**
 * @brief Initiates the building of the decision tree.
 * @param train Training dataset.
 * @param max_depth Maximum depth of the tree.
 * @param min_size Minimum size of a node before stopping further splits.
 * @return Root node of the constructed decision tree.
 */
template<typename T>
std::unique_ptr<node_t<T>> build_tree(const dataset_t<T>& train, int max_depth, int min_size) {
    auto split = get_split<T>(train);

    auto root = std::make_unique<node_t<T>>();
    root->index = split.index;
    root->value = split.value;

    recurse_split<T>(root, max_depth, min_size, 1);
    return root;
}
