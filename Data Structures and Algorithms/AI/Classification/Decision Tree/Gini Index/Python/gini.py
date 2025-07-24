def gini_index(groups, classes):
    """
    @brief Calculate the Gini index for a split dataset.

    @param groups A list of groups (each group is a list of rows) resulting from a dataset split.
    @param classes A list of all unique class labels in the dataset.

    @return The Gini index as a float value. Lower Gini indicates better purity.
    """
    n_instances = float(sum([len(group) for group in groups]))
    gini = 0.0
    for group in groups:
        size = len(group)
        if size == 0:
            continue

        score = 0.0
        for class_val in classes:
            # Proportion of class_val in the group
            p = [row[-1] for row in group].count(class_val) / size
            score += p * p
        # Weight the group’s Gini score by its relative size
        gini += (1.0 - score) * (size / n_instances)

    return gini
