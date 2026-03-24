//
// Created by GP on 22/03/2026.
//

#include "Menu.h"
#include "../algorithm/FlowNetwork.h"
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace std;

namespace {
void writeAssignmentReport(const ConferenceData& data,
                           const vector<pair<int, int>>& assignments,
                           const vector<tuple<int, int, int>>& missingReviews) {
    ofstream output(data.control.outputFilename);
    if (!output.is_open()) {
        throw runtime_error("Failed to open output file " + data.control.outputFilename);
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
}

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
    string filename;
    cout << "File: ";
    cin >> filename;

  string filepath = filename;
  if(filename.find('/') == string::npos && filename.find('\\') == string::npos) {
    if (!filesystem::exists("inputs/" + filename)) {
      filepath = "../inputs/" + filename;
    }
  }

    try {
        data = parser.parse(filepath);
        dataLoaded = true;
        cout << "Loaded " << data.submissions.size() << " submissions and "
             << data.reviewers.size() << " reviewers.\n";
    } catch(const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
}

void Menu::listSubmissions(){
    if(!dataLoaded){
      cout << "No file loaded. Use option 1 first.\n";
      return;
    }

    for(auto s : data.submissions) {
        cout << "ID: " << s.id << "\n";
        cout << "  Title:   " << s.title << "\n";
        cout << "  Authors: " << s.authors << "\n";
        cout << "  Email:   " << s.email << "\n";
        cout << "  Topic:   " << s.primary;

        if (s.secondary != -1) cout << " (secondary: " << s.secondary << ")";
        cout << "\n\n";
    }
}
void Menu::listReviewers(){
    if(!dataLoaded) {
        cout << "No file loaded. Use option 1 first.\n";
        return;
    }

    for(auto r : data.reviewers) {
        cout << "ID: " << r.id << "\n";
        cout << "  Name:   " << r.name << "\n";
        cout << "  Email:   " << r.email << "\n";
        cout << "  Topic:   " << r.primary << "\n";

        if (r.secondary != -1) cout << " (secondary: " << r.secondary << ")";
        cout << "\n\n";
    }
}
void Menu::showParameters(){
    if(!dataLoaded) {
        cout << "No file loaded. Use option 1 first.\n";
        return;
    }

    cout << "\n=== Parameters ===\n";
    cout << "Min reviews per submission:  " << data.parameters.minReviewsPerSubmission << "\n";
    cout << "Max reviews per reviewer:    " << data.parameters.maxReviewsPerReviewer << "\n";
    cout << "\n";
    cout << "Primary reviewer expertise:  " << data.parameters.primaryReviewerExpertise << "\n";
    cout << "Secondary reviewer expertise:" << data.parameters.secondaryReviewerExpertise << "\n";
    cout << "\n";
    cout << "Primary submission domain:   " << data.parameters.primarySubmissionDomain << "\n";
    cout << "Secondary submission domain: " << data.parameters.secondarySubmissionDomain << "\n";
}
void Menu::generateAssignment(){
    if(!dataLoaded) {
        cout << "No file loaded. Use option 1 first.\n";
        return;
    }

    FlowNetwork network;
    network.build(data);

    int requiredReviews = static_cast<int>(data.submissions.size()) * data.parameters.minReviewsPerSubmission;
    int maxFlow = static_cast<int>(network.solve());
    auto assignments = network.getAssignments();
    auto missingReviews = network.getMissingReviews();

    cout << "\n=== Assignment Result ===\n";
    cout << "Assigned reviews: " << maxFlow << " / " << requiredReviews << "\n";

    if (missingReviews.empty()) {
        cout << "Assignment is feasible.\n";
    } else {
        cout << "Assignment is not feasible.\n";
        cout << "Missing reviews per submission:\n";
        for (const auto& [submissionId, domain, missing] : missingReviews) {
            cout << "  Submission " << submissionId
                 << " (domain " << domain << ") is missing "
                 << missing << " review(s).\n";
        }
    }

    if (!assignments.empty()) {
        cout << "\nAssignments:\n";
        for (const auto& assignment : assignments) {
            cout << "  Submission " << assignment.first
                 << " <- Reviewer " << assignment.second << "\n";
        }
    }

    if (data.control.generateAssignments != 0) {
        try {
            writeAssignmentReport(data, assignments, missingReviews);
            cout << "\nReport written to " << data.control.outputFilename << "\n";
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
}

void Menu::runRiskAnalysis(){
    return;
}
