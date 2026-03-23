//
// Created by GP on 23/03/2026.
//

#ifndef FLOWNETWORK_H
#define FLOWNETWORK_H
#include "../graph/Graph.h"
#include "../model/ConferenceData.h"
#include <vector>

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

private:
    Graph<int> graph;
    int source;
    int sink;
    int numSubmissions;
    int numReviewers;

    bool bfs();  // encontra caminho aumentante
};
#endif //FLOWNETWORK_H
