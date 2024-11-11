import math

"""
    Time O(n)
    Space O(n)
"""

class TreeNode:
    def __init__(self, value, children):
        # Initialize a tree node with a given value and a set of children.
        self.value = value
        self.children = children  # Set of child nodes
        self.total_sum = None  # The total sum of the subtree rooted at this node

    def __repr__(self):
        # String representation for easier debugging
        return "TreeNode(%s, %s)" % (self.value, self.total_sum)

# Build the tree from a list of values and edges.
def build_tree(tree_values, tree_edges):
    # Create TreeNode objects for each value
    tree_nodes = [TreeNode(v, set()) for v in tree_values]

    # Add edges between nodes (undirected graph, so we add both directions)
    for node_from, node_to in tree_edges:
        tree_nodes[node_from - 1].children.add(tree_nodes[node_to - 1])
        tree_nodes[node_to - 1].children.add(tree_nodes[node_from - 1])
    
    # Return the root node of the tree (first node)
    return tree_nodes[0]

# Helper function to check if a number is even
def is_even_number(value):
    return not value & 1

# Populate the tree sums using DFS
def populate_tree_sums(root):
    stack = (root, None)  # Start with the root node
    visited = set()  # Set to track visited nodes

    while stack:
        selected_node = stack[0]

        if selected_node not in visited:
            # Mark the node as visited
            visited.add(selected_node)
            # Add children to the stack
            for child in selected_node.children:
                child.children.remove(selected_node)  # Remove parent link to make it a proper tree
                stack = (child, stack)  # Push child onto stack
        else:
            # Node has been visited, calculate total sum for this node
            stack = stack[-1]  # Pop from stack
            selected_node.total_sum = sum(
                map(lambda tn: tn.total_sum, selected_node.children)
            ) + selected_node.value  # Sum the children's total sums + node's value

# Function to find the best balanced forest
def find_best_balanced_forest(root):
    stack = (root, None)
    # Set to track visited nodes, visited sums, and complement sums from root
    visited, visited_sums, root_complement_sums = set(), set(), set()
    min_result_value = math.inf  # Initialize with infinity to find the minimum

    while stack:
        selected_node = stack[0]

        if selected_node not in visited:
            visited.add(selected_node)  # Mark node as visited

            # Add children to the stack for traversal
            for child in selected_node.children:
                stack = (child, stack)

            # Calculate the complement sum for this node: (TOTAL - current_sum)
            selected_sum_comp = root.total_sum - selected_node.total_sum
            root_complement_sums.add(selected_sum_comp)  # Add complement sum to the set

            # Check if splitting here forms a valid balanced forest (subtree sum * 3 should >= total sum)
            if (
                    (selected_node.total_sum * 2) in visited_sums or
                    (root.total_sum - selected_node.total_sum * 2) in visited_sums
            ) and selected_node.total_sum * 3 >= root.total_sum:
                # Calculate candidate value and update the minimum result if it's less
                candidate_value = selected_node.total_sum * 3 - root.total_sum
                min_result_value = min(min_result_value, candidate_value)
        else:
            # This block is reached when the node has been fully processed
            # Special case when two even halves are found (balanced forest with two subtrees)
            if (selected_node.total_sum * 2) == root.total_sum:
                candidate_value = selected_node.total_sum
                
                if candidate_value < min_result_value:
                    min_result_value = candidate_value

            # Check if the sum of the current node is in the visited sums or complement sums
            if (
                    (
                            selected_node.total_sum in visited_sums or
                            selected_node.total_sum in root_complement_sums
                    ) and selected_node.total_sum * 3 >= root.total_sum
            ):
                candidate_value = selected_node.total_sum * 3 - root.total_sum
                min_result_value = min(min_result_value, candidate_value)

            selected_sum_comp = root.total_sum - selected_node.total_sum
            if is_even_number(selected_sum_comp):
                selected_sum_comp_half = selected_sum_comp // 2
                
                if selected_sum_comp_half > selected_node.total_sum and (
                        selected_sum_comp_half in visited_sums or
                        selected_sum_comp_half in root_complement_sums
                ):
                    # Same candidate value if condition is met
                    candidate_value = selected_sum_comp_half - selected_node.total_sum
                    min_result_value = min(min_result_value, candidate_value)

            # Remove the complement sum from root while going up the tree
            root_complement_sums.remove(selected_sum_comp)
            visited_sums.add(selected_node.total_sum)  # Add this node's total sum to visited sums

            # Pop the node from stack as we backtrack in the DFS
            stack = stack[-1]

    # If no balanced forest was found, return -1
    if min_result_value == math.inf:
        min_result_value = -1
        
    return min_result_value

# Complete function to calculate the balanced forest
def balancedForest(tree_values, tree_edges):
    root = build_tree(tree_values, tree_edges)  # Build the tree from input values and edges
    populate_tree_sums(root)  # Populate the total sums for each node using DFS
    
    return find_best_balanced_forest(root)  # Return the minimum value of the balanced forest

