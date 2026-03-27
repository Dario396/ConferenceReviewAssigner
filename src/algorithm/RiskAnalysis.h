#ifndef RISKANALYSIS_H
#define RISKANALYSIS_H

#include "../model/ConferenceData.h"
#include <string>
#include <vector>

struct CriticalReviewer {
    int id;
    std::string name;
};

struct RiskAnalysisResult {
    bool baselineFeasible = false;
    std::vector<CriticalReviewer> criticalReviewers;
};

class RiskAnalysis {
public:
    static RiskAnalysisResult analyzeSingleReviewerFailures(const ConferenceData& data);
};

#endif //RISKANALYSIS_H
