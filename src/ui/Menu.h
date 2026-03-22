//
// Created by GP on 22/03/2026.
//

#ifndef MENU_H
#define MENU_H
class Menu {
  public:
    void run();

  private:
    void showOptions();
    void loadFile();
    void listSubmissions();
    void listReviewers();
    void showParameters();
    void generateAssignment();
    void runRiskAnalysis();
};
#endif //MENU_H
