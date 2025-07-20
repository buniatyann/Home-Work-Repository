#include <vector>
#include <stdexcept>

/**
 * @struct ConfusionMatrix
 * @brief A structure to store and compute metrics for a binary confusion matrix.
 *
 * Holds counts of True Positives (TP), True Negatives (TN), False Positives (FP),
 * and False Negatives (FN), and provides methods to calculate performance metrics.
 */
struct ConfusionMatrix {
    unsigned TP = 0;  ///< True Positives: Correctly predicted positive cases
    unsigned TN = 0;  ///< True Negatives: Correctly predicted negative cases
    unsigned FP = 0;  ///< False Positives: Incorrectly predicted positive cases
    unsigned FN = 0;  ///< False Negatives: Incorrectly predicted negative cases

    /**
     * @brief Calculates the total number of predictions.
     * @return int The sum of TP, TN, FP, and FN.
     */
    unsigned total() const {
        return TP + TN + FP + FN;
    }

    /**
     * @brief Calculates the accuracy of the model.
     * @return double Accuracy as (TP + TN) / total. Returns 0.0 if total is 0.
     */
    double accuracy() const {
        unsigned tot = total();
        return tot > 0 ? static_cast<double>(TP + TN) / tot : 0.0;
    }

    /**
     * @brief Calculates the precision of the model.
     * @return double Precision as TP / (TP + FP). Returns 0.0 if denominator is 0.
     */
    double precision() const {
        return (TP + FP) > 0 ? static_cast<double>(TP) / (TP + FP) : 0.0;
    }

    /**
     * @brief Calculates the recall (sensitivity) of the model.
     * @return double Recall as TP / (TP + FN). Returns 0.0 if denominator is 0.
     */
    double recall() const {
        return (TP + FN) > 0 ? static_cast<double>(TP) / (TP + FN) : 0.0;
    }

    /**
     * @brief Calculates the F1-score of the model.
     * @return double F1-score as 2 * (precision * recall) / (precision + recall).
     *                Returns 0.0 if denominator is 0.
     */
    double f1_score() const {
        double prec = precision();
        double rec = recall();
        return (prec + rec) > 0 ? 2 * (prec * rec) / (prec + rec) : 0.0;
    }
};

/**
 * @brief Validates that a vector contains only binary labels (0 or 1).
 * @tparam T The type of the vector elements (must be convertible to bool).
 * @param v The input vector to validate.
 * @param name The name of the vector for error reporting.
 * @throws std::invalid_argument If any element is not 0 or 1.
 */
template <typename T>
void validate_labels(const std::vector<T>& v, const std::string& name) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] != 0 && v[i] != 1) {
            throw std::invalid_argument(name + " contains invalid label at index " + std::to_string(i) + ". Only 0 or 1 allowed.");
        }
    }
}

/**
 * @brief Computes a confusion matrix from true and predicted binary labels.
 * @tparam T The type of the vector elements (must be convertible to bool).
 * @param y_true The vector of true labels (0 or 1).
 * @param y_pred The vector of predicted labels (0 or 1).
 * @return ConfusionMatrix A structure containing TP, TN, FP, and FN counts.
 * @throws std::invalid_argument If vectors have different lengths, are empty, or contain invalid labels.
 */
template <typename T>
ConfusionMatrix confusion_matrix(const std::vector<T>& y_true, const std::vector<T>& y_pred) {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors must have the same length");
    }
    if (y_true.empty()) {
        throw std::invalid_argument("Input vectors cannot be empty");
    }

    validate_labels(y_true, "y_true");
    validate_labels(y_pred, "y_pred");

    ConfusionMatrix cm;
    for (size_t i = 0; i < y_true.size(); ++i) {
        bool true_label = static_cast<bool>(y_true[i]);
        bool pred_label = static_cast<bool>(y_pred[i]);
        if (true_label && pred_label) {
            ++cm.TP;
        }
        else if (!true_label && !pred_label) {
            ++cm.TN;
        }
        else if (!true_label && pred_label) {
            ++cm.FP;
        }
        else if (true_label && !pred_label) {
            ++cm.FN;
        }
    }
    
    return cm;
}