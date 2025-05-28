#include "BucketUtils.h"

// Converts a path of bucket states into a list of textual actions.
vector<string> TraceActions(const vector<BucketState>& path, int L, int S) {
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
            actions.push_back("Fill large jug");

        // 2. Fill small bucket
        else if (currSmall > prevSmall && currBig == prevBig && currSmall == S)
            actions.push_back("Fill small jug");

        // 3. Empty large bucket
        else if (currBig < prevBig && currSmall == prevSmall && currBig == 0)
            actions.push_back("Empty large jug");

        // 4. Empty small bucket
        else if (currSmall < prevSmall && currBig == prevBig && currSmall == 0)
            actions.push_back("Empty small jug");

        // 5. Transfer from small to large bucket
        else if (currBig > prevBig && currSmall < prevSmall)
            actions.push_back("Transfer from small jug to large jug");

        // 6. Transfer from large to small bucket
        else if (currBig < prevBig && currSmall > prevSmall)
            actions.push_back("Transfer from large jug to small jug");

        // Fallback 
        else
            actions.push_back("Unknown action");
    }

    return actions;
}


// Prints the number of operations and the list of textual actions
void PrintSolution(const vector<BucketState>& path, int L, int S) {
    if (path.empty()) {
        cout << "No solution." << endl;
        return;
    }

    vector<string> actions = TraceActions(path, L, S);

    cout << "Number of operations: " << actions.size() << endl;
    cout << "Operations:" << endl;

    for (size_t i = 0; i < actions.size(); ++i) {
        cout << i + 1 << ". " << actions[i] << endl;
    }
}
