//
// Created by GP on 22/03/2026.
//

#ifndef MENU_H
#define MENU_H
#include "../model/ConferenceData.h"
#include "../parser/CSVParser.h"
#include <string>

/**
 * @brief Provides the interactive command-line interface of the application.
 */
class Menu {
public:
    /**
     * @brief Runs the menu loop until the user exits the application.
     * @complexity Depends on the selected option. Each iteration is O(1)
     * excluding the invoked operation.
     */
    void run();

private:
    ConferenceData data;
    CSVParser parser;
    bool dataLoaded = false;

    /** @brief Displays the available menu options. @complexity O(1) */
    void showOptions();
    /**
     * @brief Loads one input file into memory.
     * @complexity Dominated by CSVParser::parse.
     */
    void loadFile();
    /** @brief Prints every parsed submission. @complexity O(S) */
    void listSubmissions();
    /** @brief Prints every parsed reviewer. @complexity O(R) */
    void listReviewers();
    /** @brief Prints the currently loaded parameter set. @complexity O(1) */
    void showParameters();
    /**
     * @brief Builds the flow network, solves it, and prints the assignment.
     * @complexity Dominated by FlowNetwork::build, FlowNetwork::solve, and the
     * extraction of assignments and missing reviews.
     */
    void generateAssignment();
    /**
     * @brief Executes the risk analysis for the currently loaded instance.
     * @complexity Dominated by RiskAnalysis::analyzeSingleReviewerFailures.
     */
    void runRiskAnalysis();
};
#endif //MENU_H
