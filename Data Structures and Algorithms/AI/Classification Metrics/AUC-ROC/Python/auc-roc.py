import numpy as np

def roc_curve(truth_labels, predicted_probs):
    """
    Computes the Receiver Operating Characteristic (ROC) curve.

    @param truth_labels: List or array of ground truth binary labels (0 or 1).
    @param predicted_probs: List or array of predicted probabilities (floats in [0,1]).

    @return: Two lists - true positive rates (TPRs) and false positive rates (FPRs)
             computed at different classification thresholds.
    """
    thresholds = [0.1 * i for i in range(11)]
    tprs, fprs = [], []

    for threshold in thresholds:
        tp = fp = tn = fn = 0
        predictions = [1 if p >= threshold else 0 for p in predicted_probs]

        for i in range(len(truth_labels)):
            if predictions[i] == 1 and truth_labels[i] == 1:
                tp += 1
            elif predictions[i] == 1 and truth_labels[i] == 0:
                fp += 1
            elif predictions[i] == 0 and truth_labels[i] == 0:
                tn += 1
            elif predictions[i] == 0 and truth_labels[i] == 1:
                fn += 1

        tpr = tp / (tp + fn) if (tp + fn) > 0 else 0.0
        fpr = fp / (fp + tn) if (fp + tn) > 0 else 0.0

        tprs.append(tpr)
        fprs.append(fpr)

    return tprs, fprs


def compute_aucroc(tprs, fprs):
    """
    Computes the Area Under the ROC Curve (AUC-ROC) using the trapezoidal rule.

    @param tprs: List of true positive rates from the ROC curve.
    @param fprs: List of false positive rates from the ROC curve.

    @return: A float representing the AUC-ROC value.
    """
    aucroc = 0
    for i in range(1, len(tprs)):
        aucroc += 0.5 * abs(fprs[i] - fprs[i - 1]) * (tprs[i] + tprs[i - 1])
    
    return aucroc
