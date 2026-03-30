//
// Created by edu on 18/03/26.
//

#ifndef DA_PROJETO1_CONFERENCEDATA_H
#define DA_PROJETO1_CONFERENCEDATA_H

#include <vector>
#include "Submission.h"
#include "Reviewer.h"
#include "Parameters.h"
#include "Control.h"

/**
 * @brief Aggregates all information parsed from one conference instance.
 */
struct ConferenceData{
    /** @brief Set of submissions read from the input file. */
    std::vector<Submission> submissions;
    /** @brief Set of reviewers read from the input file. */
    std::vector<Reviewer> reviewers;
    /** @brief Assignment and scoring parameters for the instance. */
    Parameters parameters;
    /** @brief Control flags such as matching mode and output file name. */
    Control control;
};

#endif //DA_PROJETO1_CONFERENCEDATA_H
