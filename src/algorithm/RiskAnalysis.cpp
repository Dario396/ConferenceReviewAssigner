#include "RiskAnalysis.h"
#include "FlowNetwork.h"
#include <algorithm>

namespace {
int getRequiredReviews(const ConferenceData& data) {
    return static_cast<int>(data.submissions.size()) * data.parameters.minReviewsPerSubmission;
}

bool isFeasibleAssignment(const ConferenceData& data) {
    FlowNetwork network;
    network.build(data);

    const int requiredReviews = getRequiredReviews(data);
    const int maxFlow = static_cast<int>(network.solve());
    return maxFlow == requiredReviews && network.getMissingReviews().empty();
}
}

RiskAnalysisResult RiskAnalysis::analyzeSingleReviewerFailures(const ConferenceData& data) {
    RiskAnalysisResult result;
    result.baselineFeasible = isFeasibleAssignment(data);

    if (!result.baselineFeasible) {
        return result;
    }

    for (const auto& reviewer : data.reviewers) {
        ConferenceData reducedData = data;

        reducedData.reviewers.erase(
            std::remove_if(
                reducedData.reviewers.begin(),
                reducedData.reviewers.end(),
                [&](const Reviewer& currentReviewer) {
                    return currentReviewer.id == reviewer.id;
                }
            ),
            reducedData.reviewers.end()
        );

        if (!isFeasibleAssignment(reducedData)) {
            result.criticalReviewers.push_back({reviewer.id, reviewer.name});
        }
    }

    return result;
}
