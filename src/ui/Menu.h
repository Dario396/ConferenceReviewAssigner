//
// Created by GP on 22/03/2026.
//

#ifndef MENU_H
#define MENU_H
#include "../model/ConferenceData.h"
#include "../parser/CSVParser.h"
#include <string>
class Menu {
  public:
  /**
 * @brief Starts the interactive menu loop, handling user input until exit.
 */
  void run();

  private:
    ConferenceData data; ///< Stores the loaded conference data
    CSVParser parser; ///< Parser used to read input CSV files
    bool dataLoaded = false; ///< Flag indicating whether a file has been loaded


    /**
     * @brief Prints all available menu options to stdout.
     */
    void showOptions();

    /**
     * @brief Prompts the user for a filename and loads the conference data.
     * @note Expects files to be in the inputs/ directory.
     */
    void loadFile();

    /**
     * @brief Displays all loaded submissions with their details.
     * @note Requires that some file has been loaded with loadFile()
     */
    void listSubmissions();

    /**
     * @brief Displays all loaded reviewers with their details.
     * @note Requires that some file has been loaded with loadFile()
     */
    void listReviewers();

    /**
     * @brief Displays the current parameter and control settings.
     * @note Requires that some file has been loaded with loadFile()
     */
    void showParameters();


    /**
     * @brief Generates and outputs the review assignment using Max-Flow.
     * @note Requires that some file has been loaded with loadFile()
     */
    void generateAssignment();

    /**
     * @brief Runs the risk analysis based on the configured RiskAnalysis parameter.
     * @note Requires that some file has been loaded with loadFile()
     */
    void runRiskAnalysis();
};
#endif //MENU_H
