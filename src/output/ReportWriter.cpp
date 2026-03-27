#include "ReportWriter.h"
#include <fstream>
#include <stdexcept>

void writeConferenceReport(const std::string& outputPath,
                           const std::vector<std::pair<int, int>>& assignments,
                           const std::vector<std::tuple<int, int, int>>& missingReviews,
                           const RiskAnalysisResult* riskAnalysis) {
    std::ofstream output(outputPath);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open output file " + outputPath);
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

    if (riskAnalysis != nullptr) {
        if (!assignments.empty() || !missingReviews.empty()) {
            output << "\n";
        }

        output << "#RiskAnalysis\n";
        output << "BaselineFeasible," << (riskAnalysis->baselineFeasible ? 1 : 0) << "\n";
        output << "ReviewerId,ReviewerName\n";

        for (const auto& reviewer : riskAnalysis->criticalReviewers) {
            output << reviewer.id << "," << reviewer.name << "\n";
        }
    }
}
