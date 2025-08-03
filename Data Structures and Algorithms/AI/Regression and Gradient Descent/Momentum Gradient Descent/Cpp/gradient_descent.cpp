#include <vector>
#include <functional>

/**
 * @brief Alias for a cost function that takes a parameter vector and returns a double cost value.
 */
using cost_function = std::function<double(const std::vector<double>&)>;

/**
 * @brief Alias for a gradient function that takes a parameter vector and returns the gradient vector.
 */
using grad_function = std::function<std::vector<double>(const std::vector<double>&)>;

/**
 * @brief Performs momentum-based gradient descent optimization on parameters theta.
 * 
 * @param theta Vector of parameters to optimize. Updated in-place during the optimization.
 * @param momentum Vector of momentum values associated with parameters, must be same size as theta.
 * @param cost_fn Function that computes the cost given current parameters.
 * @param grad_fn Function that computes the gradient vector given current parameters.
 * @param alpha Momentum factor, typically close to 1 (default 0.9).
 * @param learning_rate Learning rate for gradient updates (default 0.01).
 * @param epochs Number of iterations to run the optimization (default 50).
 * @return std::vector<double> Vector containing the cost at each epoch.
 */
std::vector<double> momentum_gradient_descent(
    std::vector<double>& theta,
    std::vector<double>& momentum,
    cost_function cost_fn,
    grad_function grad_fn,
    double alpha = 0.9,
    double learning_rate = 0.01,
    int epochs = 50
) {
    std::vector<double> cost_history;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        // Calculate and store current cost
        double cost = cost_fn(theta);
        cost_history.push_back(cost);

        // Calculate gradient at current theta
        std::vector<double> grad = grad_fn(theta);

        // Update momentum and parameters
        for (size_t i = 0; i < theta.size(); ++i) {
            momentum[i] = alpha * momentum[i] + learning_rate * grad[i];
            theta[i] -= momentum[i];
        }
    }

    return cost_history;
}
