#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "BucketProblemSolver1.h"

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

	// Solve using method 1

	if (method == 1) {

		auto start = Clock::now();

		if (showTime == 1)
			start = Clock::now(); // start timer if needed

		BucketProblemSolver1 solver(L, S, W);
		vector<BucketState> path = solver.SolveWithBFS();
		solver.PrintSolution(path);

		if (showTime == 1) {
			auto end = Clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
			cout << "Function took " << duration << " microseconds." << endl;
		}
	}


	return 0;

}