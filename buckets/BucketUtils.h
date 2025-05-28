#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "DirectedGraph.h" 

// Converts a path of bucket states into a list of textual actions
vector<string> TraceActions(const vector<BucketState>&path, int L, int S);

// Print result
void PrintSolution(const vector<BucketState>& path, int L, int S);


