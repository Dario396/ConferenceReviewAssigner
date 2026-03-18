#include <iostream>
#include "parser/CSVParser.h"

int main() {
    try {
        ConferenceData data = CSVParser::parse("inputs/input.csv");

        std::cout << "File parsed successfully.\n";
        std::cout << "Submissions: " << data.submissions.size() << '\n';
        std::cout << "Reviewers: " << data.reviewers.size() << '\n';

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}