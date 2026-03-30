//
// Created by edu on 18/03/26.
//

#ifndef DA_PROJETO1_CSVPARSER_H
#define DA_PROJETO1_CSVPARSER_H

#include <string>
#include "../model/ConferenceData.h"

/**
 * @brief Parses project input files into a ConferenceData instance.
 */
class CSVParser {
public:
    /**
     * @brief Reads and validates one project input file.
     * @param filename Path to the input dataset.
     * @return The parsed conference instance.
     * @throws std::runtime_error If the file cannot be opened or contains
     * invalid lines, duplicated identifiers, or unknown fields.
     * @complexity O(L + S + R), where L is the number of input lines, S the
     * number of submissions, and R the number of reviewers.
     */
    static ConferenceData parse(const std::string& filename);
};

#endif //DA_PROJETO1_CSVPARSER_H
