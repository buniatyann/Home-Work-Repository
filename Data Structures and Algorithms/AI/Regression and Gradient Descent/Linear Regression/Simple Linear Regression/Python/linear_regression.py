import numpy as np
import matplotlib.pyplot as plt


def simple_linear_regression(x: np.ndarray, y: np.ndarray):
    """
    Perform simple linear regression.

    Parameters:
        x (np.ndarray): 1D array of input features.
        y (np.ndarray): 1D array of target values.

    Returns:
        m (float): Slope of the best-fit line.
        c (float): Intercept of the best-fit line.
        r_squared (float): Coefficient of determination (R² score).
    """
    if x.ndim != 1 or y.ndim != 1:
        raise ValueError("Inputs must be 1D arrays.")
    if x.size != y.size:
        raise ValueError("x and y must have the same number of elements.")
    
    mean_x = np.mean(x)
    mean_y = np.mean(y)
    
    numerator = np.sum((x - mean_x) * (y - mean_y))
    denominator = np.sum((x - mean_x) ** 2)

    if denominator == 0:
        raise ZeroDivisionError("All x values are the same. Slope is undefined.")
    
    m = numerator / denominator
    c = mean_y - m * mean_x

    # Predicted values and R²
    y_pred = m * x + c
    ss_total = np.sum((y - mean_y) ** 2)
    ss_residual = np.sum((y - y_pred) ** 2)
    r_squared = 1 - ss_residual / ss_total

    return m, c, r_squared
