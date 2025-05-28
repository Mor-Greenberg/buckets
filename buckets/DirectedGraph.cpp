#include "DirectedGraph.h"

// Creates all valid bucket states up to size n
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

// Returns sorted list of neighbors for a given node
vector<BucketState> DirectedGraph::GetAdjList(const BucketState& u) const {
    auto it = adjList.find(u);
    if (it == adjList.end())
        return {}; // empty list if node not found

    vector<BucketState> sortedNeighbors = it->second;
    sort(sortedNeighbors.begin(), sortedNeighbors.end()); // lex sort
    return sortedNeighbors;
}




