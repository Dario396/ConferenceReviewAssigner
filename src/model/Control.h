//
// Created by Dário on 05/03/2026.
//

#ifndef DA_CONTROL_H
#define DA_CONTROL_H

#include <string>

struct Control {
    int generateAssignments; ///< Controls assignment generation mode (0-3)
    int riskAnalysis; ///< Risk analysis level (0 = none, K = remove K reviewers)
    std::string outputFilename = "output.csv"; ///< Output file name
};

#endif //DA_CONTROL_H