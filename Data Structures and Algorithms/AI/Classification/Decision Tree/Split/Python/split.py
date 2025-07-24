def test_split(index, value, dataset):
    """
    @brief Splits a dataset into two groups based on a feature and a threshold value.

    @param index The index of the feature (column) to split on.
    @param value The threshold value used to divide the dataset.
    @param dataset The dataset to be split, where each row is a list and the last element is the class label.

    @return A tuple (left, right), where:
        - left contains all rows with values less than the threshold at the given index,
        - right contains all other rows.
    """
    left, right = list(), list()
    for row in dataset:
        if row[index] < value:
            left.append(row)
        else:
            right.append(row)

    return left, right

def get_split(dataset):
    """
    @brief Determines the best feature index and value to split the dataset using the Gini index.

    @param dataset The dataset to evaluate, where each row is a list and the last element is the class label.

    @return A dictionary with the best split:
        - 'index': the column index of the best feature to split on,
        - 'value': the threshold value for the best split,
        - 'groups': a tuple containing the resulting left and right groups after the split.
    """
    class_values = list(set(row[-1] for row in dataset))  # Find unique class labels
    b_index, b_value, b_score, b_groups = 999, 999, 999, None

    for index in range(len(dataset[0]) - 1):  # Exclude the class label
        for row in dataset:
            groups = test_split(index, row[index], dataset)
            gini = gini(groups, class_values)
            if gini < b_score:
                b_index, b_value, b_score, b_groups = index, row[index], gini, groups

    return {'index': b_index, 'value': b_value, 'groups': b_groups}
