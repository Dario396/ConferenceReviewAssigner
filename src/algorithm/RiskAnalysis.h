#ifndef RISKANALYSIS_H
#define RISKANALYSIS_H

#include "../model/ConferenceData.h"
#include <string>
#include <vector>

/**
 * @brief Identifies a reviewer whose removal makes the assignment infeasible.
 */
struct CriticalReviewer {
    /** @brief Identifier of the critical reviewer. */
    int id;
    /** @brief Name of the critical reviewer. */
    std::string name;
};

/**
 * @brief Stores the result of the single-reviewer failure analysis.
 */
struct RiskAnalysisResult {
    /** @brief Indicates whether the original instance is feasible. */
    bool baselineFeasible = false;
    /** @brief Reviewers whose individual failure breaks feasibility. */
    std::vector<CriticalReviewer> criticalReviewers;
};

/**
 * @brief Performs robustness checks on top of the base max-flow formulation.
 */
class RiskAnalysis {
public:
    /**
     * @brief Tests whether removing any single reviewer makes the assignment
     * impossible.
     * @param data Parsed conference instance.
     * @return The baseline feasibility and the list of critical reviewers.
     * @complexity O(R * (NM + MF)), where R is the number of reviewers,
     * N is the number of submissions, M is the number of reviewers in the
     * current network construction, and MF is the cost of one max-flow run.
     */
    static RiskAnalysisResult analyzeSingleReviewerFailures(const ConferenceData& data);
};

#endif //RISKANALYSIS_H
