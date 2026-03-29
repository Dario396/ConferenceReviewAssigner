#include "ReportWriter.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>

void writeConferenceReport(const std::string& outputPath,
                           const std::vector<ReviewAssignment>& assignments,
                           const std::vector<std::tuple<int, int, int>>& missingReviews,
                           const RiskAnalysisResult* riskAnalysis) {
    std::ofstream output(outputPath);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open output file " + outputPath);
    }

    if (!assignments.empty()) {
        output << "#SubmissionId,ReviewerId,Match\n";
        for (const auto& assignment : assignments) {
            output << assignment.submissionId << ","
                   << assignment.reviewerId << ","
                   << assignment.matchDomain << "\n";
        }

        output << "\n";

        output << "#ReviewerId,SubmissionId,Match\n";
        std::vector<ReviewAssignment> reviewerView = assignments;

        std::sort(reviewerView.begin(), reviewerView.end(),
                  [](const ReviewAssignment& a, const ReviewAssignment& b) {
                      if (a.reviewerId != b.reviewerId) {
                          return a.reviewerId < b.reviewerId;
                      }
                      return a.submissionId < b.submissionId;
                  });

        for (const auto& assignment : reviewerView) {
            output << assignment.reviewerId << ","
                   << assignment.submissionId << ","
                   << assignment.matchDomain << "\n";
        }

        output << "#Total: " << assignments.size() << "\n";
    }

    if (!missingReviews.empty()) {
        if (!assignments.empty()) {
            output << "\n";
        }

        output << "#SubmissionId,Domain,MissingReviews\n";
        for (const auto& [submissionId, domain, missing] : missingReviews) {
            output << submissionId << ","
                   << domain << ","
                   << missing << "\n";
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