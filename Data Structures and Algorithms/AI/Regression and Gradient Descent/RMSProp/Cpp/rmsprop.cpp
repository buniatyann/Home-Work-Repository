#include <vector>
#include <cmath>
#include <stdexcept>
#include <type_traits>

/**
 * @brief Performs a single RMSProp optimization step.
 * 
 * @tparam T Floating point type (float, double, etc.)
 * @param params         Parameters to be updated (modified in-place).
 * @param gradients      Gradients for each parameter.
 * @param cache          Running average of squared gradients (modified in-place).
 * @param learning_rate  Step size (default: 0.001).
 * @param rho            Decay rate for the cache (default: 0.9).
 * @param epsilon        Small constant to prevent division by zero (default: 1e-8).
 * 
 * @throws std::invalid_argument If sizes of params and gradients don't match.
 */
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
rmsprop(std::vector<T>& params,
        const std::vector<T>& gradients,
        std::vector<T>& cache,
        T learning_rate = static_cast<T>(0.001),
        T rho = static_cast<T>(0.9),
        T epsilon = static_cast<T>(1e-8))
{
    if (params.size() != gradients.size()) {
        throw std::invalid_argument("params and gradients must be the same size");
    }

    if (cache.empty()) {
        cache.resize(params.size(), T(0));
    } 
    else if (cache.size() != params.size()) {
        throw std::invalid_argument("cache must be empty or same size as params");
    }

    for (size_t i = 0; i < params.size(); ++i) {
        cache[i] = rho * cache[i] + (static_cast<T>(1) - rho) * gradients[i] * gradients[i];
        params[i] -= learning_rate * gradients[i] / (std::sqrt(cache[i]) + epsilon);
    }
}
