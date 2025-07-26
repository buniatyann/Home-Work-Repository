import numpy as np

def stochastic_gradient_descent(X, Y, learning_rate, epochs):
    """
    @brief Perform stochastic gradient descent for simple linear regression.

    @param X numpy.ndarray : Input feature array.
    @param Y numpy.ndarray : Target output array.
    @param learning_rate float : Learning rate for gradient descent.
    @param epochs int : Number of iterations to perform.

    @return tuple : Learned slope (m) and intercept (b).
    """
    m = np.random.randn()
    b = np.random.randn()

    for _ in range(epochs):
        random_index = np.random.randint(len(X))
        x = X[random_index]
        y = Y[random_index]
        pred = m * x + b
        grad_m = (pred - y) * x
        grad_b = (pred - y)
        m -= learning_rate * grad_m
        b -= learning_rate * grad_b

    return m, b
