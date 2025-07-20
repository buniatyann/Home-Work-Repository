#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>
#include <type_traits>

/**
 * @brief Computes the ROC curve.
 *
 * @tparam T Numeric type for truth labels (e.g., int, double)
 * @tparam U Numeric type for predicted probabilities (e.g., float, double)
 * @param truth_labels Vector of ground truth binary labels.
 * @param predicted_probs Vector of predicted probabilities (0 to 1).
 * @return std::tuple<std::vector<double>, std::vector<double>> TPRs and FPRs.
 */
template <
    typename T, typename U,
    typename std::enable_if<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, int>::type = 0
>
std::tuple<std::vector<double>, std::vector<double>>
roc_curve(const std::vector<T>& truth_labels,
          const std::vector<U>& predicted_probs) {
    
    std::vector<double> thresholds;
    for (int i = 0; i <= 10; ++i)
        thresholds.push_back(i * 0.1);

    std::vector<double> tprs, fprs;

    for (double threshold : thresholds) {
        int tp = 0, fp = 0, tn = 0, fn = 0;

        for (std::size_t i = 0; i < truth_labels.size(); ++i) {
            int prediction = predicted_probs[i] >= threshold ? 1 : 0;
            if (prediction == 1 && truth_labels[i] == 1) {
                ++tp;
            }
            else if (prediction == 1 && truth_labels[i] == 0) {
                ++fp;
            }
            else if (prediction == 0 && truth_labels[i] == 0) {
                ++tn;
            }
            else if (prediction == 0 && truth_labels[i] == 1) {
                ++fn;
            }
        }

        double tpr = (tp + fn) > 0 ? static_cast<double>(tp) / (tp + fn) : 0.0;
        double fpr = (fp + tn) > 0 ? static_cast<double>(fp) / (fp + tn) : 0.0;

        tprs.push_back(tpr);
        fprs.push_back(fpr);
    }

    return std::make_tuple(tprs, fprs);
}

/**
 * @brief Computes the AUC-ROC from TPR and FPR vectors.
 *
 * @param tprs Vector of TPRs.
 * @param fprs Vector of FPRs.
 * @return double AUC-ROC value.
 */
double compute_aucroc(const std::vector<double>& tprs, const std::vector<double>& fprs) {
    double auc = 0.0;
    for (std::size_t i = 1; i < tprs.size(); ++i) {
        double width = std::abs(fprs[i] - fprs[i - 1]);
        double height = (tprs[i] + tprs[i - 1]) / 2.0;
        auc += width * height;
    }
    
    return auc;
}