//
// Created by GP on 23/03/2026.
//

#ifndef FLOWNETWORK_H
#define FLOWNETWORK_H
#include "../graph/Graph.h"
#include "../model/ConferenceData.h"
#include <tuple>
#include <utility>
#include <vector>
#include <map>

/**
 * @brief Represents one review assignment between a submission and a reviewer.
 */
struct ReviewAssignment {
    int submissionId;
    int reviewerId;
    int matchDomain;
};

class FlowNetwork {
public:
    /**
     * @brief Builds the flow network from the conference data.
     * @param data The parsed conference data.
     * @complexity O(N * M) where N = submissions, M = reviewers.
     */
    void build(const ConferenceData& data);

    /**
     * @brief Runs Edmonds-Karp and returns the max flow value.
     * @complexity O(V * E^2)
     */
    double solve();

    /**
     * @brief Returns the reviewer assignments encoded by the current flow.
     * @return A list of assignments containing submission id, reviewer id and match domain.
     * @complexity O(N * M)
     */
    std::vector<ReviewAssignment> getAssignments() const;

    /**
     * @brief Returns each submission still missing reviews.
     * @return Tuples of submission id, primary domain and missing review count.
     * @complexity O(N)
     */
    std::vector<std::tuple<int, int, int>> getMissingReviews() const;

private:
    Graph<int> graph;
    int source;
    int sink;
    int numSubmissions;
    int numReviewers;
    std::vector<int> submissionIds;
    std::vector<int> submissionDomains;
    std::vector<int> reviewerIds;
    std::map<std::pair<int, int>, int> edgeMatchDomains;

    void clear();
    void addResidualEdge(int from, int to, int capacity);
    bool bfs();
};
#endif //FLOWNETWORK_H
