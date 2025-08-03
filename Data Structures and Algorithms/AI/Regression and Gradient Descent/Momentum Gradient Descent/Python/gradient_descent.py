import numpy as np
from typing import Callable

def momentum_gradient_descent(
    theta: np.ndarray,
    momentum: np.ndarray,
    cost_fn: Callable[[np.ndarray], float],
    grad_fn: Callable[[np.ndarray], np.ndarray],
    alpha: float = 0.9,
    learning_rate: float = 0.01,
    epochs: int = 50
) -> np.ndarray:
    """
    Performs momentum-based gradient descent optimization on parameters theta.

    Args:
        theta (np.ndarray): Parameter vector to optimize. Modified in place.
        momentum (np.ndarray): Momentum vector, same shape as theta.
        cost_fn (Callable[[np.ndarray], float]): Function computing the cost for given parameters.
        grad_fn (Callable[[np.ndarray], np.ndarray]): Function computing the gradient vector.
        alpha (float, optional): Momentum factor. Defaults to 0.9.
        learning_rate (float, optional): Learning rate for gradient updates. Defaults to 0.01.
        epochs (int, optional): Number of iterations. Defaults to 50.

    Returns:
        np.ndarray: Array of cost values at each epoch.
    """
    cost_history = np.zeros(epochs)

    for i in range(epochs):
        cost_history[i] = cost_fn(theta)
        grad = grad_fn(theta)
        momentum = alpha * momentum + learning_rate * grad
        theta -= momentum

    return cost_history
