//
// Created by edu on 18/03/26.
//

#ifndef DA_PROJETO1_CSVPARSER_H
#define DA_PROJETO1_CSVPARSER_H

#include <string>
#include "../model/ConferenceData.h"

class CSVParser {
    public:
        /**
        * @brief Reads and parses a CSV input file into a ConferenceData object.
        * @param filename Path to the input .csv file.
        * @return ConferenceData object containing submissions, reviewers, parameters and control settings.
        * @throws std::runtime_error if the file cannot be opened, has invalid format, or contains duplicate IDs.
        * @complexity O(N + M) where N = number of submissions, M = number of reviewers.
        */
        static ConferenceData parse(const std::string& filename);
};

#endif //DA_PROJETO1_CSVPARSER_H