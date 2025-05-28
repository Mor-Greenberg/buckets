#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "BucketProblemSolver1.h"
#include "BucketProblemSolver2.h"
#include "BucketUtils.h"


using namespace std;
using Clock = chrono::high_resolution_clock;

int main()
{
	int L, S, W, method;
	bool showTime;

	cin >> L >> S >> W >> method >> showTime;  // Read user input

	// Input validation
	if (S <= 0 || L <= 0 || W < 0 || S > L || W > L ||
		(method != 1 && method != 2) ||
		(showTime != 0 && showTime != 1)) {

		cout << "invalid input" << endl;
		exit(1);
	}

	auto start = Clock::now();

	if (showTime == 1)
		start = Clock::now(); // start timer if needed


	vector<BucketState> path;

	// Solve using method 1
	if (method == 1) {
		BucketProblemSolver1 solver(L, S, W);
		path = solver.SolveWithBFS();
	}
	// Solve using method 2
	else if (method == 2) {
		BucketProblemSolver2 solver(L, S, W);
		path = solver.Solve();
	}

	// Print the solution using shared utils
	PrintSolution(path, L, S);

	if (showTime == 1) {
		auto end = Clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
		cout << "Function took " << duration << " microseconds." << endl;
	}


	return 0;

}