import numpy as np
from typing import List, Tuple

def add_intercept_column(X: List[List[float]]) -> np.ndarray:
    """
    Adds a column of 1s at the beginning of the matrix X.
    
    Args:
        X: Input matrix (n x k) as a list of lists or numpy array
        
    Returns:
        New matrix (n x (k+1)) with a column of 1s as the first column
        
    Raises:
        ValueError: If input matrix is empty or rows have inconsistent lengths
        TypeError: If input is not numeric
    """
    X = np.asarray(X, dtype=float)
    if X.size == 0:
        raise ValueError("Input matrix X is empty")
    if not np.issubdtype(X.dtype, np.number):
        raise TypeError("Input matrix X must be numeric")
    if len(X.shape) != 2:
        raise ValueError("Input matrix X must be 2-dimensional")
    
    n = X.shape[0]
    ones = np.ones(n)[:, np.newaxis]  # column vector of 1s
    
    return np.append(ones, X, axis=1)

def multiple_linear_regression(X: List[List[float]], y: List[float]) -> Tuple[np.ndarray, float, float]:
    """
    Computes multiple linear regression coefficients and metrics.
    
    Args:
        X: Matrix of independent variables (n x k, including column of ones for intercept)
        y: Vector of dependent variables (n x 1)
        
    Returns:
        Tuple containing (coefficients, R², SS_res)
        
    Raises:
        ValueError: If inputs are empty, have mismatched dimensions, or X^T * X is singular
        TypeError: If inputs are not numeric
    """
    X = np.asarray(X, dtype=float)
    y = np.asarray(y, dtype=float)
    
    # Input validation
    if X.size == 0 or y.size == 0:
        raise ValueError("Input matrix X or vector y is empty")
    if not np.issubdtype(X.dtype, np.number) or not np.issubdtype(y.dtype, np.number):
        raise TypeError("Inputs must be numeric")
    if len(X.shape) != 2:
        raise ValueError("Input matrix X must be 2-dimensional")
    if len(y.shape) != 1:
        raise ValueError("Input vector y must be 1-dimensional")
    n, k = X.shape
    if n != y.shape[0]:
        raise ValueError("Number of rows in X must match length of y")
    
    # Compute coefficients: beta = (X^T * X)^(-1) * X^T * y
    XtX = X.T @ X
    try:
        XtX_inv = np.linalg.inv(XtX)
    except np.linalg.LinAlgError:
        raise ValueError("Matrix X^T * X is singular or nearly singular")
    
    beta = XtX_inv @ X.T @ y
    
    # predicted values: y_pred = X * beta
    y_pred = X @ beta
    
    # mean of y
    mean_y = np.mean(y)
    
    # sum of squared residuals
    residuals = y - y_pred
    ss_res = np.sum(residuals ** 2)
    
    # total sum of squares
    ss_tot = np.sum((y - mean_y) ** 2)
    
    # R²
    r_squared = 1.0 - (ss_res / ss_tot) if ss_tot != 0.0 else 1.0
    
    return (beta, r_squared, ss_res)