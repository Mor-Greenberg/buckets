#pragma once
#include "DirectedGraph.h"
#include <vector>
#include <map>
#include <queue>

using namespace std;

// Solves the bucket problem using BFS over a state graph

class BucketProblemSolver1 {
private:
    int L, S, W;                    // Bucket sizes and goal
    DirectedGraph graph;            // Graph of valid bucket states

    void BuildGraph();             // Builds all vertices and edges
    vector<BucketState> GetLegalMoves(const BucketState& state) const;   // Possible next moves

public:

    // ctor
    BucketProblemSolver1(int large, int small, int wanted);

    // Find path using BFS
    vector<BucketState> SolveWithBFS();

    // Convert path to actions
    vector<string> TraceActions(const vector<BucketState>& path) const;

    // Print result
    void PrintSolution(const vector<BucketState>& path) const;


};
