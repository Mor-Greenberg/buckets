#pragma once
#include <map>
#include <vector>
#include <utility>  
#include <algorithm> 
#include <set>
#include <iostream>


using namespace std;



typedef pair<int, int> BucketState; // Represents a state: (large bucket, small bucket)

class DirectedGraph {
private:
    map<BucketState, vector<BucketState>> adjList; // Adjacency list for each state

public:

    // Creates an empty graph with n nodes
    void MakeEmptyGraph(int n);

    // Adds a directed edge from 'from' to 'to'
    void AddEdge(const BucketState& from, const BucketState& to);

    // Returns the adjacency list of a given node 'u'
    vector<BucketState> GetAdjList(const BucketState& u) const;

    // Checks if the node 'u' exists in the graph
    bool Contains(const BucketState& u) const;

    // Returns a set of all vertices (states) in the graph
    set<BucketState> GetAllVertices() const;


    //debugg
    void PrintGraph() const {
        for (const auto& pair : adjList) {
            const BucketState& from = pair.first;
            const vector<BucketState>& neighbors = pair.second;

            cout << "(" << from.first << "," << from.second << ") -> { ";

            for (const BucketState& to : neighbors) {
                cout << "(" << to.first << "," << to.second << ") ";
            }

            cout << "}" << endl;
        }
    }

};
