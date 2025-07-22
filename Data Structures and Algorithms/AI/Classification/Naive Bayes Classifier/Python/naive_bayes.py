def calculate_prior_probabilities(y):
    """
    @brief Calculates the prior probabilities for each class in the target variable.

    @param y A pandas Series containing class labels.

    @return A pandas Series with normalized prior probabilities for each unique class.
    """
    return y.value_counts(normalize=True)


def calculate_likelihoods(X, y):
    """
    @brief Calculates likelihoods for each feature value given each class.

    This function computes P(feature=value | class) for all features and class labels.
    No smoothing is applied.

    @param X A pandas DataFrame containing categorical feature columns.
    @param y A pandas Series containing class labels.

    @return A nested dictionary of the form:
            likelihoods[feature][class][feature_value] = probability
    """
    likelihoods = {}
    for column in X.columns:
        likelihoods[column] = {}
        for class_ in y.unique():
            # Subset of data for current class
            class_data = X[y == class_][column]
            counts = class_data.value_counts()
            total_count = len(class_data)
            likelihoods[column][class_] = counts / total_count

    return likelihoods


def naive_bayes_classifier(X_test, priors, likelihoods):
    """
    @brief Performs Naive Bayes classification on the test data.

    Predicts the class for each instance in X_test using the provided prior and likelihood probabilities.

    @param X_test A pandas DataFrame containing test samples (same features as in training).
    @param priors A pandas Series with prior probabilities for each class.
    @param likelihoods A nested dictionary containing conditional probabilities 
                       of feature values given each class.

    @return A list of predicted class labels for each sample in X_test.
    """
    predictions = []
    for _, data_point in X_test.iterrows():
        class_probabilities = {}
        for class_ in priors.index:
            class_probabilities[class_] = priors[class_]
            for feature in X_test.columns:
                feature_probs = likelihoods[feature][class_]
                class_probabilities[class_] *= feature_probs.get(data_point[feature], 1 / (len(feature_probs) + 1))

        predictions.append(max(class_probabilities, key=class_probabilities.get))

    return predictions
