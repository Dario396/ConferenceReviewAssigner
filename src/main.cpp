#include <iostream>
#include <cstring>
#include <fstream>
#include <tuple>
#include <vector>
#include "algorithm/FlowNetwork.h"
#include "parser/CSVParser.h"
#include "ui/Menu.h"
using namespace std;

namespace {
void writeAssignmentReport(const string& outputPath,
                           const vector<pair<int, int>>& assignments,
                           const vector<tuple<int, int, int>>& missingReviews) {
    ofstream output(outputPath);
    if (!output.is_open()) {
        throw runtime_error("Failed to open output file " + outputPath);
    }

    if (!assignments.empty()) {
        output << "#Assignments\n";
        output << "SubmissionId,ReviewerId\n";
        for (const auto& assignment : assignments) {
            output << assignment.first << "," << assignment.second << "\n";
        }
    }

    if (!missingReviews.empty()) {
        if (!assignments.empty()) {
            output << "\n";
        }
        output << "#Submission\n";
        output << "Id,Domain,MissingReviews\n";
        for (const auto& [submissionId, domain, missing] : missingReviews) {
            output << submissionId << "," << domain << "," << missing << "\n";
        }
    }
}

int runBatchMode(const string& inputPath, const string& outputPath) {
    ConferenceData data = CSVParser::parse(inputPath);
    data.control.outputFilename = outputPath;

    FlowNetwork network;
    network.build(data);
    network.solve();

    writeAssignmentReport(outputPath, network.getAssignments(), network.getMissingReviews());
    return 0;
}
}

int main(int argc, char* argv[]) {

    /* Batch mode
     * ./myProg -b input.csv output.csv
     * skips the menu
     * read from input.csv
     * writes to output.csv (ssignments + risk management)
     * send error messages to stderr (std:cerr)
     */
    if (argc == 4 && strcmp(argv[1], "-b") == 0) {
        try {
            return runBatchMode(argv[2], argv[3]);
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    }

    Menu menu;
    menu.run();

    return 0;
}
