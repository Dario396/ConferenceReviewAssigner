#ifndef REPORTWRITER_H
#define REPORTWRITER_H

#include "../algorithm/RiskAnalysis.h"
#include <string>
#include <tuple>
#include <utility>
#include <vector>

void writeConferenceReport(const std::string& outputPath,
                           const std::vector<std::pair<int, int>>& assignments,
                           const std::vector<std::tuple<int, int, int>>& missingReviews,
                           const RiskAnalysisResult* riskAnalysis = nullptr);

#endif //REPORTWRITER_H
