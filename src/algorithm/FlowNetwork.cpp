//
// Created by GP on 23/03/2026.
//
#include "FlowNetwork.h"
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

void FlowNetwork::clear() {
  vector<int> vertices;
  for (const auto vertex : graph.getVertexSet()) {
    vertices.push_back(vertex->getInfo());
  }

  for (const int vertex : vertices) {
    graph.removeVertex(vertex);
  }

  edgeMatchDomains.clear();
  submissionIds.clear();
  submissionDomains.clear();
  reviewerIds.clear();
  source = 0;
  sink = 0;
  numSubmissions = 0;
  numReviewers = 0;
}

void FlowNetwork::addResidualEdge(int from, int to, int capacity) {
  auto fromVertex = graph.findVertex(from);
  auto toVertex = graph.findVertex(to);

  if (fromVertex == nullptr || toVertex == nullptr) {
    return;
  }

  auto forward = fromVertex->addEdge(toVertex, capacity);
  auto backward = toVertex->addEdge(fromVertex, 0);

  forward->setReverse(backward);
  backward->setReverse(forward);
  forward->setFlow(0);
  backward->setFlow(0);
}

void FlowNetwork::build(const ConferenceData& data) {
  clear();

  int N = static_cast<int>(data.submissions.size());
  int M = static_cast<int>(data.reviewers.size());
  numSubmissions = N;
  numReviewers = M;

  source = 0;
  sink = N + M + 1;

  graph.addVertex(source);
  graph.addVertex(sink);

  for(int i = 0; i < N; i++){
    int v = i + 1;
    graph.addVertex(v);
    submissionIds.push_back(data.submissions[i].id);
    submissionDomains.push_back(data.submissions[i].primary);
    addResidualEdge(source, v, data.parameters.minReviewsPerSubmission);
  }

  for(int j = 0; j < M; j++) {
    int v = N + j + 1;
    graph.addVertex(v);
    reviewerIds.push_back(data.reviewers[j].id);
    addResidualEdge(v, sink, data.parameters.maxReviewsPerReviewer);
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      bool match = false;
      int matchDomain = -1;

      const auto& sub = data.submissions[i];
      const auto& rev = data.reviewers[j];
      int mode = data.control.generateAssignments;

      if (mode == 1) {
        if (sub.primary == rev.primary) {
          match = true;
          matchDomain = sub.primary;
        }
      } else if (mode == 2) {
        if (sub.primary == rev.primary) {
          match = true;
          matchDomain = sub.primary;
        }

        else if (sub.secondary != -1 && sub.secondary == rev.primary) {
          match = true;
          matchDomain = sub.secondary;
        }

      } else if (mode == 3) {
        if (sub.primary == rev.primary) {
          match = true;
          matchDomain = sub.primary;
        }
        else if (sub.secondary != -1 && sub.secondary == rev.primary) {
          match = true;
          matchDomain = sub.secondary;
        }
        else if (rev.secondary != -1 && rev.secondary == sub.primary) {
          match = true;
          matchDomain = sub.primary;
        }
        else if (sub.secondary != -1 && rev.secondary != -1 && rev.secondary == sub.secondary) {
          match = true;
          matchDomain = sub.secondary;
        }
      }

      if (match) {
        int submissionVertex = i + 1;
        int reviewerVertex = N + j + 1;

        addResidualEdge(submissionVertex, reviewerVertex, 1);
        edgeMatchDomains[{submissionVertex, reviewerVertex}] = matchDomain;
      }
    }
  }
}

bool FlowNetwork::bfs() {
  for (const auto vertex : graph.getVertexSet()) {
    vertex->setVisited(false);
    vertex->setPath(nullptr);
  }

  auto sourceVertex = graph.findVertex(source);
  if (sourceVertex == nullptr) {
    return false;
  }

  queue<Vertex<int>*> q;
  sourceVertex->setVisited(true);
  q.push(sourceVertex);

  while (!q.empty()) {
    auto current = q.front();
    q.pop();

    for (auto edge : current->getAdj()) {
      auto next = edge->getDest();
      double residualCapacity = edge->getWeight() - edge->getFlow();

      if (residualCapacity <= 0 || next->isVisited()) {
        continue;
      }

      next->setVisited(true);
      next->setPath(edge);

      if (next->getInfo() == sink) {
        return true;
      }

      q.push(next);
    }
  }

  return false;
}

double FlowNetwork::solve() {
  double maxFlow = 0;

  while (bfs()) {
    double pathFlow = INF;
    auto current = graph.findVertex(sink);

    while (current != nullptr && current->getInfo() != source) {
      auto edge = current->getPath();
      if (edge == nullptr) {
        pathFlow = 0;
        break;
      }

      pathFlow = min(pathFlow, edge->getWeight() - edge->getFlow());
      current = edge->getOrig();
    }

    if (pathFlow <= 0) {
      break;
    }

    current = graph.findVertex(sink);
    while (current != nullptr && current->getInfo() != source) {
      auto edge = current->getPath();
      edge->setFlow(edge->getFlow() + pathFlow);
      edge->getReverse()->setFlow(edge->getReverse()->getFlow() - pathFlow);
      current = edge->getOrig();
    }

    maxFlow += pathFlow;
  }

  return maxFlow;
}

vector<ReviewAssignment> FlowNetwork::getAssignments() const {
  vector<ReviewAssignment> assignments;

  for (int i = 0; i < numSubmissions; ++i) {
    auto submissionVertex = graph.findVertex(i + 1);
    if (submissionVertex == nullptr) {
      continue;
    }

    for (const auto edge : submissionVertex->getAdj()) {
      int destination = edge->getDest()->getInfo();
      bool isReviewerEdge = destination >= numSubmissions + 1 && destination <= numSubmissions + numReviewers;

      if (!isReviewerEdge || edge->getFlow() <= 0) {
        continue;
      }

      int reviewerIndex = destination - numSubmissions - 1;
      int submissionVertexId = i + 1;
      int reviewerVertexId = destination;
      int matchDomain = edgeMatchDomains.at({submissionVertexId, reviewerVertexId});

      assignments.push_back({submissionIds[i], reviewerIds[reviewerIndex], matchDomain});
    }
  }

  sort(assignments.begin(), assignments.end(),
       [](const ReviewAssignment& a, const ReviewAssignment& b) {
         if (a.submissionId != b.submissionId) {
           return a.submissionId < b.submissionId;
         }
         return a.reviewerId < b.reviewerId;
       });

  return assignments;
}

vector<tuple<int, int, int>> FlowNetwork::getMissingReviews() const {
  vector<tuple<int, int, int>> missing;
  auto sourceVertex = graph.findVertex(source);

  if (sourceVertex == nullptr) {
    return missing;
  }

  for (const auto edge : sourceVertex->getAdj()) {
    int submissionIndex = edge->getDest()->getInfo() - 1;
    if (submissionIndex < 0 || submissionIndex >= numSubmissions) {
      continue;
    }

    int missingReviews = static_cast<int>(edge->getWeight() - edge->getFlow());
    if (missingReviews > 0) {
      missing.emplace_back(submissionIds[submissionIndex], submissionDomains[submissionIndex], missingReviews);
    }
  }

  sort(missing.begin(), missing.end());
  return missing;
}
