//
// Created by Dário on 05/03/2026.
//

#ifndef DA_REVIEWER_H
#define DA_REVIEWER_H

#include <string>

/**
 * @brief Stores the information associated with a reviewer.
 */
struct Reviewer {
    /** @brief Unique identifier of the reviewer. */
    int id;
    /** @brief Reviewer name. */
    std::string name;
    /** @brief Reviewer e-mail address. */
    std::string email;
    /** @brief Primary domain of expertise. */
    int primary;
    /** @brief Secondary domain of expertise, or -1 if absent. */
    int secondary;
};

#endif //DA_REVIEWER_H
