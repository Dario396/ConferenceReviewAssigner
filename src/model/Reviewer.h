//
// Created by Dário on 05/03/2026.
//

#ifndef DA_REVIEWER_H
#define DA_REVIEWER_H

#include <string>

struct Reviewer {
    int id; ///< Unique reviewer identifier
    std::string name; ///< Full name of the reviewer
    std::string email; ///< Contact email
    int primary; ///< Primary expertise topic
    int secondary; ///< Secondary expertise topic (-1 if not defined)
};

#endif //DA_REVIEWER_H