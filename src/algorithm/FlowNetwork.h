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
    /** @brief Identifier of the assigned submission. */
    int submissionId;
    /** @brief Identifier of the assigned reviewer. */
    int reviewerId;
    /** @brief Domain responsible for the compatibility match. */
    int matchDomain;
};

/**
 * @brief Builds and solves the flow network used in the review assignment
 * problem.
 */
class FlowNetwork {
public:
    /**
     * @brief Builds the flow network from the conference data.
     * @param data The parsed conference data.
     * @complexity O(N * M + N + M), where N is the number of submissions and
     * M is the number of reviewers.
     */
    void build(const ConferenceData& data);

    /**
     * @brief Runs Edmonds-Karp and returns the max flow value.
     * @return Maximum number of reviews that can be assigned.
     * @complexity O(V * E^2), where V is the number of vertices and E the
     * number of edges in the residual graph.
     */
    double solve();

    /**
     * @brief Returns the reviewer assignments encoded by the current flow.
     * @return A list of assignments containing submission id, reviewer id and match domain.
     * @complexity O(E log E) in the current implementation due to the final
     * sort of the extracted assignments.
     */
    std::vector<ReviewAssignment> getAssignments() const;

    /**
     * @brief Returns each submission still missing reviews.
     * @return Tuples of submission id, primary domain and missing review count.
     * @complexity O(N log N) in the current implementation due to sorting.
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

    /** @brief Clears the previously built network. @complexity O(V + E) */
    void clear();
    /**
     * @brief Adds a residual edge pair between two vertices.
     * @complexity O(1), ignoring the underlying graph insertion cost.
     */
    void addResidualEdge(int from, int to, int capacity);
    /**
     * @brief Finds one augmenting path in the residual graph using BFS.
     * @return True if the sink is reachable from the source.
     * @complexity O(V + E)
     */
    bool bfs();
};
#endif //FLOWNETWORK_H
