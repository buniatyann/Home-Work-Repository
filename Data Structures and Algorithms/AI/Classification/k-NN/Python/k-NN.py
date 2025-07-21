import math
from collections import Counter

def euclidean_distance(point1, point2):
    """
    @brief Computes the Euclidean distance between two points.
    @param point1 A list or tuple representing the first point.
    @param point2 A list or tuple representing the second point.
    @return The Euclidean distance between point1 and point2.
    """
    squares = [(p - q) ** 2 for p, q in zip(point1, point2)]
    return math.sqrt(sum(squares))

def k_nearest_neighbors(data, query, k, distance_fn):
    """
    @brief Performs k-nearest neighbors classification.
    @param data A list of tuples where each element is (features, label).
    @param query A list or tuple representing the query point to classify.
    @param k The number of nearest neighbors to consider.
    @param distance_fn A function that computes the distance between two points.
    @return The predicted label (based on majority vote) for the query point.
    """
    neighbor_distances_and_indices = []

    for idx, label in enumerate(data):
        distance = distance_fn(label[0], query)
        neighbor_distances_and_indices.append((distance, idx))

    sorted_neighbor_distances_and_indices = sorted(neighbor_distances_and_indices)
    k_nearest_distances_and_indices = sorted_neighbor_distances_and_indices[:k]
    k_nearest_labels = [data[i][1] for _, i in k_nearest_distances_and_indices]

    most_common = Counter(k_nearest_labels).most_common(1)
    return most_common[0][0]
