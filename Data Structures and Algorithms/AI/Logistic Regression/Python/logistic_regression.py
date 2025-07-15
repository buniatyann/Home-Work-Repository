import numpy as np

def sigmoid(z):
    """
    @brief Applies the sigmoid function element-wise.
    @param z Input scalar, vector, or array.
    @return The sigmoid of the input.
    """
    return 1 / (1 + np.exp(-z))


def cost_function(h, y):
    """
    @brief Computes the binary cross-entropy loss.
    @param h Predicted probabilities (from sigmoid function).
    @param y Ground truth labels (0 or 1).
    @return Mean cross-entropy loss.
    """
    return (-y * np.log(h) - (1 - y) * np.log(1 - h)).mean()


def logistic_regression(X, y, num_iterations, learning_rate):
    """
    @brief Trains a logistic regression model using gradient descent.
    @param X Input feature matrix (shape: [n_samples, n_features]).
    @param y Target vector (shape: [n_samples]).
    @param num_iterations Number of iterations for gradient descent.
    @param learning_rate Learning rate for parameter updates.
    @return Optimized parameter vector (theta), including bias term.
    """
    # Add intercept to X
    intercept = np.ones((X.shape[0], 1))
    X = np.concatenate((intercept, X), axis=1)

    # Weights initialization
    theta = np.zeros(X.shape[1])

    for i in range(num_iterations):
        z = np.dot(X, theta)
        h = sigmoid(z)
        gradient = np.dot(X.T, (h - y)) / y.size
        theta -= learning_rate * gradient

        # Optional loss computation for monitoring
        # z = np.dot(X, theta)
        # h = sigmoid(z)
        # loss = cost_function(h, y)
        # if i % 10000 == 0:
        #     print(f'Loss after {i} iterations: {loss}\t')

    return theta


def predict_prob(X, theta):
    """
    @brief Computes predicted probabilities using learned parameters.
    @param X Input feature matrix (shape: [n_samples, n_features]).
    @param theta Model parameters, including bias term (shape: [n_features + 1]).
    @return Predicted probabilities (shape: [n_samples]).
    """
    intercept = np.ones((X.shape[0], 1))
    X_b = np.concatenate([intercept, X], axis=1)
    
    return sigmoid(X_b @ theta)


def predict(X, theta, threshold=0.5):
    """
    @brief Converts predicted probabilities to binary class predictions.
    @param X Input feature matrix (shape: [n_samples, n_features]).
    @param theta Model parameters, including bias term.
    @param threshold Classification threshold (default: 0.5).
    @return Boolean array of predictions (True for class 1, False for class 0).
    """
    return predict_prob(X, theta) >= threshold
