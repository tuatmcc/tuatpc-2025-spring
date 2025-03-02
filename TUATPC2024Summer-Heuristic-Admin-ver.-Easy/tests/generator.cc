#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int N_MIN = 1;
const int N_MAX = 200000;

const long long Ai_MIN = 1;
const long long Ai_MAX = 1000000000;

const long long Bi_MIN = 1;
const long long Bi_MAX = 1000000000;


void gen(const string name, const int n, const pair<vector<long long>, vector<long long>> ab) {
	ofstream of(name);

	of << n << '\n';
	for (int i = 0; i < n; ++i)
		of << ab.first[i] << " \n"[i == n-1];
	for (int i = 0; i < n; ++i)
		of << ab.second[i] << " \n"[i == n-1];
}

pair<vector<long long>, vector<long long>> random_testcases(
	int random_n, long long single_max, long long _sum_max) {
	pair<vector<long long>, vector<long long>> ab;
	long long single_assert = Ai_MIN, sum_assert = 0, sum_max = _sum_max;
	ab.first = vector<long long>(random_n);
	ab.second = vector<long long>(random_n);
	
	for (int i = 0; i < random_n; ++i) {
		long long a, b;
		a = rnd.next(Ai_MIN, max(min(min(sum_max, single_max), sum_max - (random_n - i) * Ai_MIN), Ai_MIN));
		b = rnd.next(Bi_MIN, max(min(min(sum_max, single_max), sum_max - (random_n - i) * Bi_MIN), Bi_MIN));

		if (i == random_n - 1 && max(a, b) < sum_max) {
			if (a > b)
				a = min(sum_max, single_max);
			else
				b = min(sum_max, single_max);
		}

		sum_max -= max(a, b);

		single_assert = max(single_assert, max(a, b));
		sum_assert += max(a, b);

		ab.first[i] = a;
		ab.second[i] = b;
	}

	assert(single_assert <= single_max);
	assert(sum_assert <= _sum_max);
	return ab;
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

	// Random max(max(Ai, Bi)) < 1600 && sum of max(Ai, Bi) < 4200
	for (int t = 0; t < 10; ++t) {
		pair<vector<long long>, vector<long long>> testcase;
		int random_n = rnd.next(N_MIN, 4199);

		testcase = random_testcases(random_n, 1599, 4199);
		gen(format("10_random_%02d.in", t).c_str(), random_n, testcase);
	}

	// Random max(max(Ai, Bi)) <= 1600 && sum of max(Ai, Bi) < 4200
	for (int t = 0; t < 10; ++t) {
		pair<vector<long long>, vector<long long>> testcase;
		int random_n = rnd.next(N_MIN, 4199);

		testcase = random_testcases(random_n, 1600, 4199);
		gen(format("11_random_%02d.in", t).c_str(), random_n, testcase);
	}

	// Random max(max(Ai, Bi)) < 1600 && sum of max(Ai, Bi) <= 4200
	for (int t = 0; t < 10; ++t) {
		pair<vector<long long>, vector<long long>> testcase;
		int random_n = rnd.next(N_MIN, 4200);

		testcase = random_testcases(random_n, 1599, 4200);
		gen(format("12_random_%02d.in", t).c_str(), random_n, testcase);
	}

	// Random max(max(Ai, Bi)) <= 1600 && sum of max(Ai, Bi) <= 4200
	for (int t = 0; t < 10; ++t) {
		pair<vector<long long>, vector<long long>> testcase;
		int random_n = rnd.next(N_MIN, 4200);

		testcase = random_testcases(random_n, 1600, 4200);
		gen(format("13_random_%02d.in", t).c_str(), random_n, testcase);
	}

	// All random
	for (int t = 0; t < 5; ++t) {
		pair<vector<long long>, vector<long long>> testcase;
		int random_n = rnd.next(N_MIN, N_MAX);

		testcase = random_testcases(random_n, Ai_MAX, LLONG_MAX);
		gen(format("14_random_%02d.in", t).c_str(), random_n, testcase);
	}

	// N == 1
	gen("20_handmade_01.in", 1, {{1700}, {4300}});

	// N == 2
	gen("20_handmade_02.in", 2, {{2000, 5000}, {2000, 5000}});

	// max(max(Ai, Bi)) == 1600 && sum of max(Ai, Bi) == 4200
	gen("20_handmade_03.in", 5, {{1600, 300, 300, 300, 300}, {1000, 650, 650, 650, 650}});

	// Min
	gen("30_min_01.in", 5, {{Ai_MIN, Ai_MIN, Ai_MIN, Ai_MIN, Ai_MIN}, {Bi_MIN, Bi_MIN, Bi_MIN, Bi_MIN, Bi_MIN}});

	// Max
	gen("30_max_01.in", 5, {{Ai_MAX, Ai_MAX, Ai_MAX, Ai_MAX, Ai_MAX}, {Bi_MAX, Bi_MAX, Bi_MAX, Bi_MAX, Bi_MAX}});

	// N == N_MAX
	for (int t = 0; t < 5; ++t) {
		pair<vector<long long>, vector<long long>> n_max_case;

		n_max_case = random_testcases(N_MAX, Ai_MAX, LLONG_MAX);
		gen(format("40_max_%02d.in", t).c_str(), N_MAX, n_max_case);
	}
	return 0;
}
