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

        output << "#Risk Analysis: 1\n";

        for (size_t i = 0; i < riskAnalysis->criticalReviewers.size(); ++i) {
            if (i > 0) {
                output << ", ";
            }
            output << riskAnalysis->criticalReviewers[i].id;
        }

        output << "\n";
    }
}
