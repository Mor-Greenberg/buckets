#include "BucketProblemSolver1.h"


// Constructor: stores L, S, W and builds the graph
BucketProblemSolver1::BucketProblemSolver1(int large, int small, int wanted): L(large), S(small), W(wanted) {
    BuildGraph();
}

// builds all vertices and edges
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

// Converts a path of bucket states into a list of textual actions.
vector<string> BucketProblemSolver1::TraceActions(const vector<BucketState>& path) const {
    vector<string> actions;

    // Start from the second state and compare with the previous one
    for (size_t i = 1; i < path.size(); ++i) {
        BucketState prev = path[i - 1];
        BucketState curr = path[i];

        int prevBig = prev.first;
        int prevSmall = prev.second;
        int currBig = curr.first;
        int currSmall = curr.second;

        // 1. Fill large bucket
        if (currBig > prevBig && currSmall == prevSmall && currBig == L)
            actions.push_back("Fill large bucket");

        // 2. Fill small bucket
        else if (currSmall > prevSmall && currBig == prevBig && currSmall == S)
            actions.push_back("Fill small bucket");

        // 3. Empty large bucket
        else if (currBig < prevBig && currSmall == prevSmall && currBig == 0)
            actions.push_back("Empty large bucket");

        // 4. Empty small bucket
        else if (currSmall < prevSmall && currBig == prevBig && currSmall == 0)
            actions.push_back("Empty small bucket");

        // 5. Transfer from small to large bucket
        else if (currBig > prevBig && currSmall < prevSmall)
            actions.push_back("Transfer from small to large bucket");

        // 6. Transfer from large to small bucket
        else if (currBig < prevBig && currSmall > prevSmall)
            actions.push_back("Transfer from large to small bucket");

        // Fallback 
        else
            actions.push_back("Unknown action");
    }

    return actions;
}


void BucketProblemSolver1::PrintSolution(const vector<BucketState>& path) const {
    if (path.empty()) {
        cout << "No solution." << endl;
        return;
    }

    vector<string> actions = TraceActions(path);

    cout << "Number of operations: " << actions.size() << endl;
    cout << "Operations:" << endl;

    for (size_t i = 0; i < actions.size(); ++i) {
        cout << i + 1 << ". " << actions[i] << endl;
    }
}


