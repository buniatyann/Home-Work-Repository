import numpy as np
from typing import Tuple

def cost(X: np.ndarray, y: np.ndarray, theta: np.ndarray) -> float:
    """
    Compute the Mean Squared Error cost.

    Parameters
    ----------
    X : np.ndarray
        Feature matrix (m x n).
    y : np.ndarray
        Target values (m, ).
    theta : np.ndarray
        Model parameters (n, ).

    Returns
    -------
    float
        Mean squared error.
    """
    m = y.shape[0]
    predictions = X.dot(theta)
    
    return (1 / m) * np.sum((predictions - y) ** 2)


def gradient_descent(X: np.ndarray, y: np.ndarray,
    theta: np.ndarray, alpha: float, iterations: int) -> Tuple[np.ndarray, np.ndarray, np.ndarray]:
    """
    Perform batch gradient descent using NumPy.

    Parameters
    ----------
    X : np.ndarray
        Feature matrix (m x n).
    y : np.ndarray
        Target values (m, ).
    theta : np.ndarray
        Initial parameters (n, ).
    alpha : float
        Learning rate.
    iterations : int
        Number of iterations.

    Returns
    -------
    tuple of (theta, cost_history, theta_history)
        theta : np.ndarray
            Optimized parameters.
        cost_history : np.ndarray
            Cost after each iteration.
        theta_history : np.ndarray
            Theta values after each iteration (iterations x n).
    """
    m = y.shape[0]
    cost_history = np.zeros(iterations)
    theta_history = np.zeros((iterations, theta.shape[0]))

    for i in range(iterations):
        predictions = X.dot(theta)
        error = predictions - y
        gradient = (1 / m) * X.T.dot(error)
        theta -= alpha * gradient

        theta_history[i] = theta
        cost_history[i] = cost(X, y, theta)

    return theta, cost_history, theta_history
