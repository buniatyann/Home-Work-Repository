import numpy as np
from typing import Tuple

def dot_product(a: np.ndarray, b: np.ndarray) -> float:
    if a.shape != b.shape:
        raise ValueError("dot_product: vectors must be of the same shape")
    
    return float(np.dot(a, b))

def mean_squared_error(dataset: np.ndarray, labels: np.ndarray, theta: np.ndarray, theta_0: float) -> float:
    if dataset.shape[1] != theta.shape[0]:
        raise ValueError("mean_squared_error: dataset and theta must have compatible dimensions")
    
    n = dataset.shape[0]
    predictions = dataset @ theta + theta_0  # shape (n,)
    diffs = predictions - labels
    
    return float(np.mean(diffs ** 2))

def test_error(dataset: np.ndarray, labels: np.ndarray, theta: np.ndarray, theta_0: float) -> float:
    return mean_squared_error(dataset, labels, theta, theta_0)

def random_linear_classifier(dataset: np.ndarray, labels: np.ndarray, k_trials: int) -> Tuple[np.ndarray, float]:
    dim = dataset.shape[1]
    best_theta = None
    best_theta_0 = 0.0
    min_error = float('inf')

    for _ in range(k_trials):
        theta = np.random.uniform(-1.0, 1.0, dim)
        theta_0 = np.random.uniform(-1.0, 1.0)

        error = mean_squared_error(dataset, labels, theta, theta_0)
        if error < min_error:
            min_error = error
            best_theta = theta
            best_theta_0 = theta_0

    return best_theta, best_theta_0

def cross_validate(dataset: np.ndarray, labels: np.ndarray, k_trials: int) -> Tuple[np.ndarray, float]:
    return random_linear_classifier(dataset, labels, k_trials)
