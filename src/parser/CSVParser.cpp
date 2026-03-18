//
// Created by edu on 18/03/26.
//

#include <fstream>
#include <stdexcept>
#include "CSVParser.h"

ConferenceData CSVParser::parse(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed open file " + filename);
    }
    ConferenceData data;
    return data;
}