//
// Created by edu on 18/03/26.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "CSVParser.h"


enum class Section {
    None,
    Submissions,
    Reviewers,
    Parameters,
    Control
};

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;

    while (std::getline(ss, field, delimiter)) {
        fields.push_back(trim(field));
    }

    if (!line.empty() && line.back() == delimiter) {
        fields.push_back("");
    }
    return fields;
}

ConferenceData CSVParser::parse(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed open file " + filename);
    }
    ConferenceData data;
    std::string line;
    Section currentSection = Section::None;
    while (std::getline(file, line)) {
        if (line == "#Submissions") {
            currentSection = Section::Submissions;
            continue;
        }

        if (line == "#Reviewers") {
            currentSection = Section::Reviewers;
            continue;
        }

        if (line == "#Parameters") {
            currentSection = Section::Parameters;
            continue;
        }

        if (line == "#Control") {
            currentSection = Section::Control;
            continue;
        }

        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        line = trim(line);

        if (line.empty()) continue;

        if (currentSection == Section::Submissions) {
            std::vector<std::string> fields = split(line, ',');

            if (fields.size() != 6) {
                throw std::runtime_error("Invalid submission line: " + line);
            }

            Submission submission;
            submission.id = std::stoi(fields[0]);
            submission.title = fields[1];
            submission.authors = fields[2];
            submission.email = fields[3];
            submission.primary = std::stoi(fields[4]);
            submission.secondary = fields[5].empty() ? -1 : std::stoi(fields[5]);

            data.submissions.push_back(submission);
        }

        if (currentSection == Section::Reviewers) {
            std::vector<std::string> fields = split(line, ',');

            if (fields.size() != 5) {
                throw std::runtime_error("Invalid submission line: " + line);
            }

            Reviewer reviewer;
            reviewer.id = std::stoi(fields[0]);
            reviewer.name = fields[1];
            reviewer.email = fields[2];
            reviewer.primary = std::stoi(fields[3]);
            reviewer.secondary = fields[4].empty() ? -1 : std::stoi(fields[4]);

            data.reviewers.push_back(reviewer);
        }
    }
    return data;
}