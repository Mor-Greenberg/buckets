#pragma once
#include <map>
#include <vector>
#include <utility>  
#include <algorithm> 
#include <set>
#include <iostream>


using namespace std;

typedef pair<int, int> BucketState; // Represents a state: (large bucket, small bucket)

// Directed graph represented using adjacency lists
class DirectedGraph {
private:
    map<BucketState, vector<BucketState>> adjList; // Adjacency list for each state

public:

    // Initialize all nodes
    void MakeEmptyGraph(int n);

    // Adds a directed edge from 'from' to 'to'
    void AddEdge(const BucketState& from, const BucketState& to);

    // Returns the adjacency list of a given node 'u'
    vector<BucketState> GetAdjList(const BucketState& u) const;

   

    
};
