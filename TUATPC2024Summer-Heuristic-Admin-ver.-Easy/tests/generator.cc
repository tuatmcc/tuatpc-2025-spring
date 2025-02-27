#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int N_MIN = 1;
const int N_MAX = 200000;

const long long Hi_MIN = 1;
const long long Hi_MAX = 1000000000;

const long long Ai_MIN = 1;
const long long Ai_MAX = 1000000000;

void gen(const string name, const int n, const pair<vector<long long>, vector<long long>> ah) {
	ofstream of(name);

	of << n << '\n';
	for (int i = 0; i < n; ++i)
		of << ah.first[i] << " \n"[i == n-1];
	for (int i = 0; i < n; ++i)
		of << ah.second[i] << " \n"[i == n-1];
}


int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	pair<vector<long long>, vector<long long>> s1, s2, s3, s4, s5;

	// Sample 1
	s1 = {
		{200, 300, 100},
		{500, 400, 50},
	};
	gen("00_sample_01.in", 3, s1);

	// Sample 2
	s2 = {
		{1500, 1500, 1500, 1500, 1500},
		{1500, 1500, 1500, 1500, 1500},
	};
	gen("00_sample_02.in", 5, s2);

	// Sample 3
	s3 = {
		{2000, 300, 300},
		{2000, 300, 300},
	};
	gen("00_sample_03.in", 3, s3);

	// Sample 4
	s4 = {
		{1000000000},
		{1000000000},
	};
	gen("00_sample_04.in", 1, s4);

	// Sample 5
	s5 = {
		{4229, 4229, 4229},
		{2383, 2383, 2383},
	};
	gen("00_sample_05.in", 3, s5);

	// Random Ai >= 1600 && Hi >= 4200
	for (int t = 0; t < 10; ++t) {
		int random_n = rnd.next(N_MIN, N_MAX);
		pair<vector<long long>, vector<long long>> random_case(vector<long long>(random_n, 0), vector<long long>(random_n, 0));

		for (int i = 0; i < random_n; ++i) {
			long long a, h;
			a = rnd.next(1600LL, Ai_MAX);
			h = rnd.next(4200LL, Hi_MAX);
			random_case.first[i] = a;
			random_case.second[i] = h;
		}

		gen(format("10_random_large_%02d.in", t).c_str(), random_n, random_case);
	}

	// Random Ai <= 1600 && Hi <= 4200
	for (int t = 0; t < 10; ++t) {
		int random_n = rnd.next(N_MIN, N_MAX);
		pair<vector<long long>, vector<long long>> random_case(vector<long long>(random_n, 0), vector<long long>(random_n, 0));

		for (int i = 0; i < random_n; ++i) {
			long long a, h;
			a = rnd.next(Ai_MIN, 1600LL);
			h = rnd.next(Hi_MIN, 4200LL);
			random_case.first[i] = a;
			random_case.second[i] = h;
		}

		gen(format("11_random_small_%02d.in", t).c_str(), random_n, random_case);
	}
	
	// Random Ai <= 1600 && Hi >= 4200
	for (int t = 0; t < 10; ++t) {
		int random_n = rnd.next(N_MIN, N_MAX);
		pair<vector<long long>, vector<long long>> random_case(vector<long long>(random_n, 0), vector<long long>(random_n, 0));

		for (int i = 0; i < random_n; ++i) {
			long long a, h;
			a = rnd.next(Ai_MIN, 1600LL);
			h = rnd.next(4200LL, Hi_MAX);
			random_case.first[i] = a;
			random_case.second[i] = h;
		}

		gen(format("12_random_mixed_%02d.in", t).c_str(), random_n, random_case);
	}

	// Random Ai >= 1600 && Hi <= 4200
	for (int t = 0; t < 10; ++t) {
		int random_n = rnd.next(N_MIN, N_MAX);
		pair<vector<long long>, vector<long long>> random_case(vector<long long>(random_n, 0), vector<long long>(random_n, 0));

		for (int i = 0; i < random_n; ++i) {
			long long a, h;
			a = rnd.next(1600LL, Ai_MAX);
			h = rnd.next(Hi_MIN, 4200LL);
			random_case.first[i] = a;
			random_case.second[i] = h;
		}

		gen(format("13_random_mixed_%02d.in", t).c_str(), random_n, random_case);
	}

	// N == 1
	gen("20_handmade_01.in", 1, {{1700}, {4300}});

	// N == 2
	gen("20_handmade_02.in", 2, {{2000, 5000}, {2000, 5000}});

	// Min
	gen("30_min_01.in", 5, {{Ai_MIN, Ai_MIN, Ai_MIN, Ai_MIN, Ai_MIN}, {Hi_MIN, Hi_MIN, Hi_MIN, Hi_MIN, Hi_MIN}});

	// Max
	gen("30_max_01.in", 5, {{Ai_MAX, Ai_MAX, Ai_MAX, Ai_MAX, Ai_MAX}, {Hi_MAX, Hi_MAX, Hi_MAX, Hi_MAX, Hi_MAX}});

	// N == N_MAX
	for (int t = 0; t < 10; ++t) {
		pair<vector<long long>, vector<long long>> n_max_case(vector<long long>(N_MAX, 0), vector<long long>(N_MAX, 0));
		for (int i = 0; i < N_MAX; ++i) {
			long long a, h;
			a = rnd.next(Ai_MIN, Ai_MAX);
			h = rnd.next(Hi_MIN, Hi_MAX);
			n_max_case.first[i] = a;
			n_max_case.second[i] = h;
		}
		gen(format("40_max_%02d.in", t).c_str(), N_MAX, n_max_case);
	}
	return 0;
}
