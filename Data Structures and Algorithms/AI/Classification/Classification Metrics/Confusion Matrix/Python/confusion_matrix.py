import numpy as np

class ConfusionMatrix:
    """
    @brief A class to store and compute metrics for a binary confusion matrix.

    Attributes:
        TP (int): True Positives - Correctly predicted positive cases.
        TN (int): True Negatives - Correctly predicted negative cases.
        FP (int): False Positives - Incorrectly predicted positive cases.
        FN (int): False Negatives - Incorrectly predicted negative cases.
    """
    def __init__(self):
        self.TP = 0
        self.TN = 0
        self.FP = 0
        self.FN = 0

    def total(self):
        """
        @brief Calculates the total number of predictions.

        @return int The sum of TP, TN, FP, and FN.
        """
        return self.TP + self.TN + self.FP + self.FN

    def accuracy(self):
        """
        @brief Calculates the accuracy of the model.

        @return float Accuracy as (TP + TN) / total. Returns 0.0 if total is 0.
        """
        tot = self.total()
        return (self.TP + self.TN) / tot if tot > 0 else 0.0

    def precision(self):
        """
        @brief Calculates the precision of the model.

        @return float Precision as TP / (TP + FP). Returns 0.0 if denominator is 0.
        """
        return self.TP / (self.TP + self.FP) if (self.TP + self.FP) > 0 else 0.0

    def recall(self):
        """
        @brief Calculates the recall (sensitivity) of the model.

        @return float Recall as TP / (TP + FN). Returns 0.0 if denominator is 0.
        """
        return self.TP / (self.TP + self.FN) if (self.TP + self.FN) > 0 else 0.0

    def f1_score(self):
        """
        @brief Calculates the F1-score of the model.

        @return float F1-score as 2 * (precision * recall) / (precision + recall).
               Returns 0.0 if denominator is 0.
        """
        prec = self.precision()
        rec = self.recall()
        return 2 * (prec * rec) / (prec + rec) if (prec + rec) > 0 else 0.0


def validate_labels(y: np.ndarray, name: str) -> None:
    """
    @brief Validates that an array contains only binary labels (0 or 1).

    @param y np.ndarray The input array to validate.
    @param name str The name of the array for error reporting.

    @throws ValueError If any element is not 0 or 1.
    """
    if not np.all(np.isin(y, [0, 1])):
        invalid_idx = np.where(~np.isin(y, [0, 1]))[0][0]
        raise ValueError(f"{name} contains invalid label at index {invalid_idx}. Only 0 or 1 allowed.")


def confusion_matrix(y_true: np.ndarray, y_pred: np.ndarray) -> ConfusionMatrix:
    """
    @brief Computes a confusion matrix from true and predicted binary labels.

    @param y_true np.ndarray Array of true labels (0 or 1).
    @param y_pred np.ndarray Array of predicted labels (0 or 1).

    @return ConfusionMatrix A class instance containing TP, TN, FP, and FN counts.

    @throws ValueError If arrays have different lengths, are empty, or contain invalid labels.
    """
    if y_true.shape != y_pred.shape:
        raise ValueError("Arrays must have the same shape")
    if y_true.size == 0:
        raise ValueError("Input arrays cannot be empty")

    validate_labels(y_true, "y_true")
    validate_labels(y_pred, "y_pred")

    cm = ConfusionMatrix()
    cm.TP = np.sum((y_true == 1) & (y_pred == 1))
    cm.TN = np.sum((y_true == 0) & (y_pred == 0))
    cm.FP = np.sum((y_true == 0) & (y_pred == 1))
    cm.FN = np.sum((y_true == 1) & (y_pred == 0))
    
    return cm
