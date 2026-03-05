//
// Created by Dário on 05/03/2026.
//

#ifndef DA_SUBMISSION_H
#define DA_SUBMISSION_H

#include <string>

struct Submission {
    int id;
    std::string title;
    std::string authors;
    std::string email;
    int primary;
    int secondary;
};

#endif //DA_SUBMISSION_H