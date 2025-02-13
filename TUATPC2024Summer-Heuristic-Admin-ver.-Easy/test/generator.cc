#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int N_MIN = 1;
const int N_MAX = 200000;

const int Hi_MIN = 1;
const int Hi_MAX = 1000000000;

const int Ai_MIN = 1;
const int Ai_MAX = 1000000000;

void gen(const string name, const int n, const vector<pair<long long, long long>> ah) {
	ofstream of(name);

	for (int i = 0; i < n; ++i)
		of << ah[i].first << " " << ah[i].second;
}


int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	vector<pair<long long, long long>> s1, s2, s3;

	// Sample 1
	s1 = {
		{200, 500},
		{300, 400},
		{100, 50},
	};
	gen("00_sample_01.in", 3, s1);

	// Sample 2
	s2 = {
		{1500, 1500},
		{1500, 1500},
		{1500, 1500},
		{1500, 1500},
		{1500, 1500},
	};
	gen("00_sample_02.in", 5, s2);

	// Sample 3
	s3 = {
		{1000000000, 1000000000},
	};
	gen("00_sample_03.in", 1, s3);

	// Random
	for (int t = 0; t < 20; ++t) {
		int random_n = rnd.next(N_MIN, N_MAX);
		vector<pair<long long, long long>> random_case(random_n);

		for (int i = 0; i < random_n; ++i) {
			long long a, h;
			a = rnd.next(Ai_MIN, Ai_MAX);
			h = rnd.next(Hi_MIN, Hi_MAX);
			random_case[i] = {a, h};
		}

		gen(format("10_random_%02d.in", t).c_str(), random_n, random_case);
	}

	// N == 1
	gen("20_handmade_01.in", 1, {{1700, 4300}});

	// N == 2
	gen("20_handmade_02.in", 2, {{2000, 2000}, {5000, 5000}});

	// Min
	gen("30_min_01.in", 5, {{Ai_MIN, Hi_MIN}, {Ai_MIN, Hi_MIN}, {Ai_MIN, Hi_MIN}, {Ai_MIN, Hi_MIN}, {Ai_MIN, Hi_MIN}});

	// Max
	gen("30_max_01.in", 5, {{Ai_MAX, Hi_MAX}, {Ai_MAX, Hi_MAX}, {Ai_MAX, Hi_MAX}, {Ai_MAX, Hi_MAX}, {Ai_MAX, Hi_MAX}});

	// N == N_MAX
	vector<pair<long long, long long>> n_max_case(N_MAX);
	for (int i = 0; i < N_MAX; ++i) {
		long long a, h;
		a = rnd.next(Ai_MIN, Ai_MAX);
		h = rnd.next(Hi_MIN, Hi_MAX);
		n_max_case[i] = {a ,h};
	}
	gen("30_max_02.in", N_MAX, n_max_case);
	return 0;
}
