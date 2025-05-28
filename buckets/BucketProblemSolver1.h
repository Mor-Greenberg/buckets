#pragma once
#include "DirectedGraph.h"
#include <vector>
#include <map>
#include <queue>

using namespace std;


class BucketProblemSolver1 {
private:
    int L, S, W;                    // bucket sizes and goal
    DirectedGraph graph;

    void BuildGraph();             // builds all vertices and edges
    vector<BucketState> GetLegalMoves(const BucketState& state) const;

public:
    BucketProblemSolver1(int large, int small, int wanted);

    // Runs BFS from (0,0) to (W,0)
    vector<BucketState> SolveWithBFS();

    vector<string> TraceActions(const vector<BucketState>& path) const;

    void PrintSolution(const vector<BucketState>& path) const;


};
