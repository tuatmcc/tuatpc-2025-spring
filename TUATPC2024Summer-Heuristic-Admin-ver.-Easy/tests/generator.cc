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

	of << n << endl;
	for (int i = 0; i < n; ++i)
		of << ah[i].first << " " << ah[i].second << endl;
}


int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	vector<pair<long long, long long>> s1, s2, s3, s4, s5;

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
		{2000, 2000},
		{300, 300},
		{300, 300},
	};
	gen("00_sample_03.in", 3, s3);

	// Sample 4
	s4 = {
		{1000000000, 1000000000},
	};
	gen("00_sample_04.in", 1, s4);

	// Sample 5
	s5 = {
		{4229, 2383},
		{4229, 2383},
		{4229, 2383},
	};
	gen("00_sample_05.in", 3, s5);

	// Random Ai >= 1600 && Hi >= 4200
	for (int t = 0; t < 10; ++t) {
		int random_n = rnd.next(N_MIN, N_MAX);
		vector<pair<long long, long long>> random_case(random_n);

		for (int i = 0; i < random_n; ++i) {
			long long a, h;
			a = rnd.next(1600, Ai_MAX);
			h = rnd.next(4200, Hi_MAX);
			random_case[i] = {a, h};
		}

		gen(format("10_random_large_%02d.in", t).c_str(), random_n, random_case);
	}

	// Random Ai <= 1600 && Hi <= 4200
	for (int t = 0; t < 10; ++t) {
		int random_n = rnd.next(N_MIN, N_MAX);
		vector<pair<long long, long long>> random_case(random_n);

		for (int i = 0; i < random_n; ++i) {
			long long a, h;
			a = rnd.next(Ai_MIN, 1600);
			h = rnd.next(Hi_MIN, 4200);
			random_case[i] = {a, h};
		}

		gen(format("11_random_small_%02d.in", t).c_str(), random_n, random_case);
	}
	
	// Random Ai <= 1600 && Hi >= 4200
	for (int t = 0; t < 10; ++t) {
		int random_n = rnd.next(N_MIN, N_MAX);
		vector<pair<long long, long long>> random_case(random_n);

		for (int i = 0; i < random_n; ++i) {
			long long a, h;
			a = rnd.next(Ai_MIN, 1600);
			h = rnd.next(4200, Hi_MAX);
			random_case[i] = {a, h};
		}

		gen(format("12_random_mixed_%02d.in", t).c_str(), random_n, random_case);
	}

	// Random Ai >= 1600 && Hi <= 4200
	for (int t = 0; t < 10; ++t) {
		int random_n = rnd.next(N_MIN, N_MAX);
		vector<pair<long long, long long>> random_case(random_n);

		for (int i = 0; i < random_n; ++i) {
			long long a, h;
			a = rnd.next(1600, Ai_MAX);
			h = rnd.next(Hi_MIN, 4200);
			random_case[i] = {a, h};
		}

		gen(format("13_random_mixed_%02d.in", t).c_str(), random_n, random_case);
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
	for (int t = 0; t < 10; ++t) {
		vector<pair<long long, long long>> n_max_case(N_MAX);
		for (int i = 0; i < N_MAX; ++i) {
			long long a, h;
			a = rnd.next(Ai_MIN, Ai_MAX);
			h = rnd.next(Hi_MIN, Hi_MAX);
			n_max_case[i] = {a, h};
		}
		gen(format("40_max_%02d.in", t).c_str(), N_MAX, n_max_case);
	}
	return 0;
}
