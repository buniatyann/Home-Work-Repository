import numpy as np

def gradient_descent(X, y, learning_rate=0.01, batch_size=16, epochs=100):
    """
    @brief Performs mini-batch gradient descent for linear regression.

    @param X Input feature matrix of shape (m, n), where m is the number of samples and n is the number of features.
    @param y Target vector of shape (m, 1) or (m,).
    @param learning_rate Learning rate for gradient descent updates.
    @param batch_size Number of samples per mini-batch.
    @param epochs Number of passes over the entire dataset.

    @return Optimized parameter vector theta of shape (n, 1).
    """
    m, n = X.shape
    theta = np.random.randn(n, 1)

    for epoch in range(epochs):
        shuffled_indices = np.random.permutation(m)
        X_shuffled = X[shuffled_indices]
        y_shuffled = y[shuffled_indices]

        for i in range(0, m, batch_size):
            xi = X_shuffled[i:i + batch_size]
            yi = y_shuffled[i:i + batch_size]
            gradients = 2 / batch_size * xi.T.dot(xi.dot(theta) - yi)
            theta = theta - learning_rate * gradients

    return theta
