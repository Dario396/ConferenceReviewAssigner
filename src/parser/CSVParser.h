//
// Created by edu on 18/03/26.
//

#ifndef DA_PROJETO1_CSVPARSER_H
#define DA_PROJETO1_CSVPARSER_H

#include <string>
#include "../model/ConferenceData.h"

class CSVParser {
    public:
        static ConferenceData parse(const std::string& filename);
};

#endif //DA_PROJETO1_CSVPARSER_H