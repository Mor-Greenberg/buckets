#include "DirectedGraph.h"

// Creates an empty graph with n nodes
void DirectedGraph::MakeEmptyGraph(int n) {
    for (int big = 0; big < n; ++big) {
        for (int small = 0; small < n; ++small) {
            BucketState state = { big, small };
            adjList[state] = {}; // Initialize with empty neighbor list
        }
    }
}

// Add the neighbor 'to' to the adjacency list of 'from'
void DirectedGraph::AddEdge(const BucketState& from, const BucketState& to) {
    adjList[from].push_back(to);
}

vector<BucketState> DirectedGraph::GetAdjList(const BucketState& u) const {
    auto it = adjList.find(u);
    if (it == adjList.end())
        return {}; // empty list if node not found

    vector<BucketState> sortedNeighbors = it->second;
    sort(sortedNeighbors.begin(), sortedNeighbors.end()); // lex sort
    return sortedNeighbors;
}

bool DirectedGraph::Contains(const BucketState& u) const {
    return adjList.find(u) != adjList.end();
}

set<BucketState> DirectedGraph::GetAllVertices() const {
    set<BucketState> vertices;
    for (const auto& pair : adjList) {
        vertices.insert(pair.first);
    }
    return vertices;
}

