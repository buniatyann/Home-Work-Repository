"""
Decision Tree implementation for classification.

This module provides functions to build a decision tree by recursively splitting
the dataset based on feature values, creating terminal nodes when stopping
criteria are met.
"""

def create_terminal(group):
    """
    Creates a terminal node by selecting the most common outcome in the group.

    Args:
        group (list): List of data rows, where each row's last element is the outcome.

    Returns:
        The most frequent outcome in the group.
    """
    outcomes = [row[-1] for row in group]
    return max(set(outcomes), key=outcomes.count)

def build_tree(train, max_depth, min_size):
    """
    Builds a decision tree from the training dataset.

    Args:
        train (list): Training dataset as a list of rows.
        max_depth (int): Maximum depth of the tree.
        min_size (int): Minimum number of samples required to split.

    Returns:
        dict: Root node of the decision tree.
    """
    root = get_split(train)
    recurse_split(root, max_depth, min_size, 1)
    return root

def recurse_split(node, max_depth, min_size, depth):
    """
    Recursively splits nodes to build the decision tree.

    Args:
        node (dict): Current node containing groups to split.
        max_depth (int): Maximum depth of the tree.
        min_size (int): Minimum number of samples required to split.
        depth (int): Current depth in the tree.
    """
    left, right = node['groups']
    del(node['groups'])
    
    # Handle empty groups by creating a terminal node
    if not left or not right:
        node['left'] = node['right'] = create_terminal(left + right)
        return
    
    # Stop splitting if max depth is reached
    if depth >= max_depth:
        node['left'] = create_terminal(left)
        node['right'] = create_terminal(right)
        return
    
    # Process left group
    if len(left) <= min_size:
        node['left'] = create_terminal(left)
    else:
        node['left'] = get_split(left)
        recurse_split(node['left'], max_depth, min_size, depth + 1)
    
    # Process right group
    if len(right) <= min_size:
        node['right'] = create_terminal(right)
    else:
        node['right'] = get_split(right)
        recurse_split(node['right'], max_depth, min_size, depth + 1)