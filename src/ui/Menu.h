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
    void run();

  private:
    ConferenceData data;
    CSVParser parser;
    bool dataLoaded = false;

    void showOptions();
    void loadFile();
    void listSubmissions();
    void listReviewers();
    void showParameters();
    void generateAssignment();
    void runRiskAnalysis();
};
#endif //MENU_H
