//
// Created by edu on 18/03/26.
//

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
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

std::vector<std::string> splitRespectingQuotes(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool insideQuotes = false;

    for (char c : line) {
        if (c == '"') {
            insideQuotes = !insideQuotes;  // entra/sai das aspas
        } else if (c == ',' && !insideQuotes) {
            fields.push_back(trim(field)); // fim de campo
            field.clear();
        } else {
            field += c;  // acumula o caracter
        }
    }
    fields.push_back(trim(field)); // último campo
    return fields;
}

ConferenceData CSVParser::parse(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file " + filename);
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
            std::vector<std::string> fields = splitRespectingQuotes(line);

            if (fields.size() < 5 || fields.size() > 6) {
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
            continue;
        }

        if (currentSection == Section::Reviewers) {
            std::vector<std::string> fields = splitRespectingQuotes(line);

            if (fields.size() != 5) {
                throw std::runtime_error("Invalid reviewer line: " + line);
            }

            Reviewer reviewer;
            reviewer.id = std::stoi(fields[0]);
            reviewer.name = fields[1];
            reviewer.email = fields[2];
            reviewer.primary = std::stoi(fields[3]);
            reviewer.secondary = fields[4].empty() ? -1 : std::stoi(fields[4]);

            data.reviewers.push_back(reviewer);
            continue;
        }

        if (currentSection == Section::Parameters) {
            std::vector<std::string> fields = splitRespectingQuotes(line);

            if (fields.size() != 2) {
                throw std::runtime_error("Invalid parameter line: " + line);
            }

            std::string parameterName = fields[0];
            int value = std::stoi(fields[1]);

            if (parameterName == "MinReviewsPerSubmission") {
                data.parameters.minReviewsPerSubmission = value;
            }

            else if (parameterName == "MaxReviewsPerReviewer") {
                data.parameters.maxReviewsPerReviewer = value;
            }

            else if (parameterName == "PrimaryReviewerExpertise") {
                data.parameters.primaryReviewerExpertise = value;
            }

            else if (parameterName == "SecondaryReviewerExpertise") {
                data.parameters.secondaryReviewerExpertise = value;
            }

            else if (parameterName == "PrimarySubmissionDomain") {
                data.parameters.primarySubmissionDomain = value;
            }

            else if (parameterName == "SecondarySubmissionDomain") {
                data.parameters.secondarySubmissionDomain = value;
            }
            else {
                throw std::runtime_error("Unknown parameter: " + parameterName);
            }
            continue;
        }

        if (currentSection == Section::Control) {
            std::vector<std::string> fields = splitRespectingQuotes(line);

            if (fields.size() != 2) {
                throw std::runtime_error("Invalid control line: " + line);
            }

            std::string parameterName = fields[0];

            if (parameterName == "GenerateAssignments") {
                int value = std::stoi(fields[1]);
                data.control.generateAssignments = value;
            }

            else if (parameterName == "RiskAnalysis") {
                int value = std::stoi(fields[1]);
                data.control.riskAnalysis = value;
            }

            else if (parameterName == "OutputFileName") {
                data.control.outputFilename = fields[1];
            }
            else {
                throw std::runtime_error("Unknown control parameter: " + parameterName);
            }
            continue;
        }
    }

    std::unordered_set<int> submissionIds;
    for (const auto& s : data.submissions) {
        if (!submissionIds.insert(s.id).second) {
            throw std::runtime_error("Duplicate submission ID: " + std::to_string(s.id));
        }
    }

    std::unordered_set<int> reviewerIds;
    for (const auto& r : data.reviewers) {
        if (!reviewerIds.insert(r.id).second) {
            throw std::runtime_error("Duplicate reviewer ID: " + std::to_string(r.id));
        }
    }

    return data;
}