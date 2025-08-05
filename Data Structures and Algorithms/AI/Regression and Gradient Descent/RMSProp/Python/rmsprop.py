import numpy as np

def rmsprop(params, gradients, cache, learning_rate=0.001, decay_rate=0.9, epsilon=1e-8):
    """    
    @param params        np.ndarray: Parameters to be updated.
    @param gradients     np.ndarray: Gradients of the parameters.
    @param cache         np.ndarray: Cache for moving average of squared gradients.
    @param learning_rate float: Learning rate (default: 0.001).
    @param decay_rate    float: Decay rate for moving average (default: 0.9).
    @param epsilon       float: Small value to prevent division by zero (default: 1e-8).

    @return tuple: A tuple containing:
        - Updated parameters (np.ndarray)
        - Updated cache (np.ndarray)
    """
    # Initialize cache if empty
    if cache.size == 0:
        cache = np.zeros_like(params)
    
    # Update cache: cache = decay * cache + (1 - decay) * gradient^2
    cache = decay_rate * cache + (1 - decay_rate) * np.square(gradients)
    
    # Update parameters: param -= learning_rate * gradient / (sqrt(cache) + epsilon)
    params = params - learning_rate * gradients / (np.sqrt(cache) + epsilon)
    
    return params, cache
