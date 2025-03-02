#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using ll = long long;

const int N_MIN = 1;
const int N_MAX = 200000;

const ll Bi_MIN = 1;
const ll Bi_MAX = 1000000000;

const ll Ai_MIN = 1;
const ll Ai_MAX = 1000000000;

int main(int argc, char *argv[]) {
	registerValidation(argc, argv);
	int N;

	N = inf.readInt(N_MIN, N_MAX, "N");
	inf.readEoln();

	for (int i = 0; i < N; ++i) {
		inf.readLong(Ai_MIN, Ai_MAX, "A");

		if (i != N - 1)
			inf.readSpace();
		else if (i == N - 1)
			inf.readEoln();
	}

	for (int i = 0; i < N; ++i) {
		inf.readLong(Bi_MIN, Bi_MAX, "B");

		if (i != N - 1)
			inf.readSpace();
		else if (i == N - 1)
			inf.readEoln();
	}

	inf.readEof();
	return 0;
}