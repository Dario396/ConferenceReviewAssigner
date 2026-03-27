//
// Created by Dário on 05/03/2026.
//

#ifndef DA_PARAMETERS_H
#define DA_PARAMETERS_H

struct Parameters {
    int minReviewsPerSubmission; ///< Minimum reviews required per submission
    int maxReviewsPerReviewer; ///< Maximum reviews required per submission

    int primaryReviewerExpertise; ///< Weight for primary reviewer expertise match
    int secondaryReviewerExpertise; ///< Weight for secondary reviewer expertise match

    int primarySubmissionDomain; ///< Weight for primary submission domain match
    int secondarySubmissionDomain; ///< Weight for secondary submission domain match
};


#endif //DA_PARAMETERS_H