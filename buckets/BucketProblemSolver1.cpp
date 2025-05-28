#include "BucketProblemSolver1.h"


// Ctor
BucketProblemSolver1::BucketProblemSolver1(int large, int small, int wanted): L(large), S(small), W(wanted) {
    BuildGraph();
}

// Builds all vertices and edges
void BucketProblemSolver1::BuildGraph() {
    int n = max(L, S) + 1;
    graph.MakeEmptyGraph(n); // adds all (big, small) states to the graph

    for (int big = 0; big <= L; ++big) {
        for (int small = 0; small <= S; ++small) {
            BucketState state = { big, small };
            vector<BucketState> nextStates = GetLegalMoves(state);

            for (const BucketState& next : nextStates) {
                graph.AddEdge(state, next);
            }
        }
    }
}

// Possible next moves
vector<BucketState> BucketProblemSolver1::GetLegalMoves(const BucketState& state) const {
    vector<BucketState> moves;
    int big = state.first;
    int small = state.second;

    // 1. Fill large bucket
    if (big < L)
        moves.push_back({ L, small });

    // 2. Fill small bucket
    if (small < S)
        moves.push_back({ big, S });

    // 3. Empty large bucket
    if (big > 0)
        moves.push_back({ 0, small });

    // 4. Empty small bucket
    if (small > 0)
        moves.push_back({ big, 0 });

    // 5. Transfer from small to large
    if (small > 0 && big < L) {
        int transfer = min(small, L - big);
        moves.push_back({ big + transfer, small - transfer });
    }

    // 6. Transfer from large to small
    if (big > 0 && small < S) {
        int transfer = min(big, S - small);
        moves.push_back({ big - transfer, small + transfer });
    }

    return moves;
}

// Find path using BFS
vector<BucketState> BucketProblemSolver1::SolveWithBFS() {
    queue<BucketState> q;                      // Queue for BFS
    map<BucketState, BucketState> parent;      
    set<BucketState> visited;                  // Set of visited states

    BucketState start = { 0, 0 };                // Initial state: both buckets empty
    BucketState goal = { W, 0 };                 // Target state: large bucket has W, small bucket is empty

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        BucketState current = q.front();
        q.pop();

        // If we reached the goal, reconstruct the path
        if (current == goal) {
            vector<BucketState> path;
            for (BucketState state = goal; state != start; state = parent[state]) {
                path.push_back(state);
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path; // Return the path from start to goal
        }

        // Explore all neighbors (legal moves)
        for (const BucketState& neighbor : graph.GetAdjList(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current; // Remember how we got to this state
                q.push(neighbor);
            }
        }
    }

    // No path found
    return {};
}


