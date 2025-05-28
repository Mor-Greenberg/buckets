#pragma once
#pragma once
#include <vector>
#include "DirectedGraph.h" 

using namespace std;

// This class solves the Bucket Problem using BFS without building the full graph
class BucketProblemSolver2 {
private:
    int L, S, W; 

    // Given a current state, calculates all legal neighbor states 
    vector<BucketState> CalculateAdjList(const BucketState& state) const;

    // Checks whether a state is the goal state (large bucket has W and small bucket is empty)
    bool IsGoal(const BucketState& state) const;

public:
    // Ctor
    BucketProblemSolver2(int large, int small, int wanted);

    // Solves the problem using BFS and returns the path of states from start to goal
    vector<BucketState> Solve();

};
