//
// Created by Dário on 05/03/2026.
//

#ifndef DA_PARAMETERS_H
#define DA_PARAMETERS_H

/**
 * @brief Stores the configuration parameters used by the assignment tool.
 */
struct Parameters {
    /** @brief Minimum number of reviews required for each submission. */
    int minReviewsPerSubmission;
    /** @brief Maximum number of reviews a reviewer may perform. */
    int maxReviewsPerReviewer;

    /** @brief Weight associated with reviewer primary expertise. */
    int primaryReviewerExpertise;
    /** @brief Weight associated with reviewer secondary expertise. */
    int secondaryReviewerExpertise;

    /** @brief Weight associated with submission primary domain. */
    int primarySubmissionDomain;
    /** @brief Weight associated with submission secondary domain. */
    int secondarySubmissionDomain;
};

#endif //DA_PARAMETERS_H
