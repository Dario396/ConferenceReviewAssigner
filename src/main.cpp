#include <iostream>
#include <cstring>
#include <fstream>
#include <tuple>
#include <vector>
#include "algorithm/FlowNetwork.h"
#include "algorithm/RiskAnalysis.h"
#include "output/ReportWriter.h"
#include "parser/CSVParser.h"
#include "ui/Menu.h"
using namespace std;

int runBatchMode(const string& inputPath, const string& outputPath) {
    ConferenceData data = CSVParser::parse(inputPath);
    data.control.outputFilename = outputPath;

    FlowNetwork network;
    network.build(data);
    network.solve();

    RiskAnalysisResult riskAnalysis;
    RiskAnalysisResult* riskAnalysisPtr = nullptr;
    if (data.control.riskAnalysis != 0) {
        riskAnalysis = RiskAnalysis::analyzeSingleReviewerFailures(data);
        riskAnalysisPtr = &riskAnalysis;
    }

    writeConferenceReport(outputPath, network.getAssignments(), network.getMissingReviews(), riskAnalysisPtr);
    return 0;
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
