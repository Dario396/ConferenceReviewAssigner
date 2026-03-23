//
// Created by GP on 23/03/2026.
//
#include "FlowNetwork.h"

void FlowNetwork::build(const ConferenceData& data) {
  int N = data.submissions.size();
  int M = data.reviewers.size();

  source = 0;
  sink = N + M + 1;

  graph.addVertex(source);
  graph.addVertex(sink);

  for(int i = 0; i < N; i++){
    int v = i + 1;
    graph.addVertex(v);
    graph.addEdge(source, v, data.parameters.minReviewsPerSubmission);
  }

  for(int j = 0; j < M; j++) {
    int v = N + j + 1;
    graph.addVertex(v);
    graph.addEdge(v, sink, data.parameters.maxReviewsPerReviewer);
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      bool match = false;
      const auto& sub = data.submissions[i];
      const auto& rev = data.reviewers[j];
      int mode = data.control.generateAssignments;

      if (mode == 1) {
        match = (sub.primary == rev.primary);
      } else if (mode == 2) {
        match = (sub.primary == rev.primary) ||
                (sub.secondary != -1 && sub.secondary == rev.primary);
      } else if (mode == 3) {
        match = (sub.primary == rev.primary) ||
                (sub.secondary != -1 && sub.secondary == rev.primary) ||
                (rev.secondary != -1 && sub.primary == rev.secondary) ||
                (sub.secondary != -1 && rev.secondary != -1 && sub.secondary == rev.secondary);
      }

      if (match) {
        graph.addEdge(i + 1, N + j + 1, 1);
      }
    }
  }
}