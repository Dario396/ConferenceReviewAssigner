//
// Created by Dário on 05/03/2026.
//

#ifndef DA_SUBMISSION_H
#define DA_SUBMISSION_H

#include <string>

struct Submission {
    int id; ///< Unique submission identifier
    std::string title; ///< Title of the paper
    std::string authors; ///< Author(s) of the paper
    std::string email; ///< Contact email
    int primary; ///< Primary topic identifier
    int secondary; ///< Secondary topic identifier (-1 if not defined)
};

#endif //DA_SUBMISSION_H