#include "BucketProblemSolver2.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <functional>


// Hash function for BucketState (pair<int, int>)
namespace std {
    template<>
    struct hash<BucketState> {
        size_t operator()(const BucketState& bs) const {
            return hash<int>()(bs.first) ^ (hash<int>()(bs.second) << 1);
        }
    };
}


// Ctor
BucketProblemSolver2::BucketProblemSolver2(int large, int small, int wanted): L(large), S(small), W(wanted) {}


// Checks if the current state is the goal: large bucket contains W, small is empty
bool BucketProblemSolver2::IsGoal(const BucketState& state) const {
    return state.first == W && state.second == 0;
}

// Returns all valid next states from a given state
vector<BucketState> BucketProblemSolver2::CalculateAdjList(const BucketState& state) const {
    vector<BucketState> neighbors;
    int big = state.first;
    int small = state.second;

    // 1. Fill large bucket
    if (big < L)
        neighbors.emplace_back(L, small);

    // 2. Fill small bucket
    if (small < S)
        neighbors.emplace_back(big, S);

    // 3. Empty large bucket
    if (big > 0)
        neighbors.emplace_back(0, small);

    // 4. Empty small bucket
    if (small > 0)
        neighbors.emplace_back(big, 0);

    // 5. Transfer from small to large
    int transfer1 = min(small, L - big);
    if (transfer1 > 0)
        neighbors.emplace_back(big + transfer1, small - transfer1);

    // 6. Transfer from large to small
    int transfer2 = min(big, S - small);
    if (transfer2 > 0)
        neighbors.emplace_back(big - transfer2, small + transfer2);

    return neighbors;
}

// Solves the problem using BFS and returns the path to the goal
vector<BucketState> BucketProblemSolver2::Solve() {
    unordered_map<BucketState, BucketState> parent;
    unordered_set<BucketState> visited;
    queue<BucketState> q;

    BucketState start(0, 0);
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        BucketState current = q.front();
        q.pop();

        if (IsGoal(current)) {
            // Reconstruct path
            vector<BucketState> path;
            while (current != start) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (const BucketState& neighbor : CalculateAdjList(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    // No solution
    return {};
}
