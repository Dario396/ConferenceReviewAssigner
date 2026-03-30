//
// Created by Dário on 05/03/2026.
//

#ifndef DA_SUBMISSION_H
#define DA_SUBMISSION_H

#include <string>

/**
 * @brief Stores the information associated with a conference submission.
 */
struct Submission {
    /** @brief Unique identifier of the submission. */
    int id;
    /** @brief Title of the submitted paper. */
    std::string title;
    /** @brief Author list as read from the input file. */
    std::string authors;
    /** @brief Contact e-mail of the submission. */
    std::string email;
    /** @brief Primary domain of the submission. */
    int primary;
    /** @brief Secondary domain of the submission, or -1 if absent. */
    int secondary;
};

#endif //DA_SUBMISSION_H
