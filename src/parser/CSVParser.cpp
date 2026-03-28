//
// Created by edu on 18/03/26.
//

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include "CSVParser.h"

enum class InputBlock {
    None,
    Submissions,
    Reviewers,
    Parameters,
    Control
};

std::string stripSpaces(const std::string& text) {
    size_t first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }

    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

std::vector<std::string> splitCsvKeepingQuotes(const std::string& line) {
    std::vector<std::string> tokens;
    std::string currentToken;
    bool quotedField = false;

    for (char ch : line) {
        if (ch == '"') {
            quotedField = !quotedField;
        } else if (ch == ',' && !quotedField) {
            tokens.push_back(stripSpaces(currentToken));
            currentToken.clear();
        } else {
            currentToken += ch;
        }
    }

    tokens.push_back(stripSpaces(currentToken));
    return tokens;
}

ConferenceData CSVParser::parse(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file " + filename);
    }

    ConferenceData data;
    std::string line;
    InputBlock activeBlock = InputBlock::None;

    while (std::getline(file, line)) {
        if (line == "#Submissions") {
            activeBlock = InputBlock::Submissions;
            continue;
        }

        if (line == "#Reviewers") {
            activeBlock = InputBlock::Reviewers;
            continue;
        }

        if (line == "#Parameters") {
            activeBlock = InputBlock::Parameters;
            continue;
        }

        if (line == "#Control") {
            activeBlock = InputBlock::Control;
            continue;
        }

        size_t commentStart = line.find('#');
        if (commentStart != std::string::npos) {
            line = line.substr(0, commentStart);
        }

        line = stripSpaces(line);

        if (line.empty()) {
            continue;
        }

        if (activeBlock == InputBlock::Submissions) {
            std::vector<std::string> tokens = splitCsvKeepingQuotes(line);

            if (tokens.size() < 5 || tokens.size() > 6) {
                throw std::runtime_error("Invalid submission line: " + line);
            }

            Submission submission;
            submission.id = std::stoi(tokens[0]);
            submission.title = tokens[1];
            submission.authors = tokens[2];
            submission.email = tokens[3];
            submission.primary = std::stoi(tokens[4]);
            submission.secondary = tokens[5].empty() ? -1 : std::stoi(tokens[5]);

            data.submissions.push_back(submission);
            continue;
        }

        if (activeBlock == InputBlock::Reviewers) {
            std::vector<std::string> tokens = splitCsvKeepingQuotes(line);

            if (tokens.size() != 5) {
                throw std::runtime_error("Invalid reviewer line: " + line);
            }

            Reviewer reviewer;
            reviewer.id = std::stoi(tokens[0]);
            reviewer.name = tokens[1];
            reviewer.email = tokens[2];
            reviewer.primary = std::stoi(tokens[3]);
            reviewer.secondary = tokens[4].empty() ? -1 : std::stoi(tokens[4]);

            data.reviewers.push_back(reviewer);
            continue;
        }

        if (activeBlock == InputBlock::Parameters) {
            std::vector<std::string> tokens = splitCsvKeepingQuotes(line);

            if (tokens.size() != 2) {
                throw std::runtime_error("Invalid parameter line: " + line);
            }

            std::string entryKey = tokens[0];
            int parsedValue = std::stoi(tokens[1]);

            if (entryKey == "MinReviewsPerSubmission") {
                data.parameters.minReviewsPerSubmission = parsedValue;
            }
            else if (entryKey == "MaxReviewsPerReviewer") {
                data.parameters.maxReviewsPerReviewer = parsedValue;
            }
            else if (entryKey == "PrimaryReviewerExpertise") {
                data.parameters.primaryReviewerExpertise = parsedValue;
            }
            else if (entryKey == "SecondaryReviewerExpertise") {
                data.parameters.secondaryReviewerExpertise = parsedValue;
            }
            else if (entryKey == "PrimarySubmissionDomain") {
                data.parameters.primarySubmissionDomain = parsedValue;
            }
            else if (entryKey == "SecondarySubmissionDomain") {
                data.parameters.secondarySubmissionDomain = parsedValue;
            }
            else {
                throw std::runtime_error("Unknown parameter: " + entryKey);
            }

            continue;
        }

        if (activeBlock == InputBlock::Control) {
            std::vector<std::string> tokens = splitCsvKeepingQuotes(line);

            if (tokens.size() != 2) {
                throw std::runtime_error("Invalid control line: " + line);
            }

            std::string entryKey = tokens[0];

            if (entryKey == "GenerateAssignments") {
                data.control.generateAssignments = std::stoi(tokens[1]);
            }
            else if (entryKey == "RiskAnalysis") {
                data.control.riskAnalysis = std::stoi(tokens[1]);
            }
            else if (entryKey == "OutputFileName") {
                data.control.outputFilename = tokens[1];
            }
            else {
                throw std::runtime_error("Unknown control parameter: " + entryKey);
            }

            continue;
        }
    }

    std::unordered_set<int> seenSubmissionIds;
    for (const auto& submission : data.submissions) {
        if (!seenSubmissionIds.insert(submission.id).second) {
            throw std::runtime_error("Duplicate submission ID: " + std::to_string(submission.id));
        }
    }

    std::unordered_set<int> seenReviewerIds;
    for (const auto& reviewer : data.reviewers) {
        if (!seenReviewerIds.insert(reviewer.id).second) {
            throw std::runtime_error("Duplicate reviewer ID: " + std::to_string(reviewer.id));
        }
    }

    return data;
}