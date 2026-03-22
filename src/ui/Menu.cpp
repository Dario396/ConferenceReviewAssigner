//
// Created by GP on 22/03/2026.
//

#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::run() {
    int option;

    do {
        showOptions();

        if(!(cin >> option)){
            cin.clear();
            cin.ignore(1000, '\n');
            option = -1;
        }

        switch (option) {
            case 1: loadFile(); break;
            case 2: listSubmissions(); break;
            case 3: listReviewers(); break;
            case 4: showParameters(); break;
            case 5: generateAssignment(); break;
            case 6: runRiskAnalysis(); break;
            case 0: cout << "Bye\n"; break;
            default: cout << "Invalid Option.\n";
        }
    } while (option != 0);
}

void Menu::showOptions(){
    cout << "\n=== Conference Review Tool ===\n";
    cout << "1. Load input file\n";
    cout << "2. Display list of submissions\n";
    cout << "3. Display list of reviewers\n";
    cout << "4. Display current paramenters\n";
    cout << "5. Generate review assignment\n";
    cout << "6. Run risk analysis\n";
    cout << "0. Exit\n";
    cout << "Option: ";
}

void Menu::loadFile(){
  return;
}

void Menu::listSubmissions(){
    return;
}
void Menu::listReviewers(){
    return;
}
void Menu::showParameters(){
    return;
}
void Menu::generateAssignment(){
    return;
}
void Menu::runRiskAnalysis(){
    return;
}