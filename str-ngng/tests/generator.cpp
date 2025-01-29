#include "testlib.h"
#include "bits/stdc++.h"
#include "constraints.hpp"
#include <filesystem>

using namespace std;

void gen(const string name, const string S, const vector<pair<int, int>>& LR)
{
    ofstream ofs(name);
    ofs << S.size() << " " << LR.size() << endl;
    ofs << S << endl;
    for (auto [l, r] : LR) {
        ofs << l << " " << r << endl;
    }
}

struct Settings {
    int N_MIN, N_MAX;
    int Q_MIN, Q_MAX;
    Settings(int N_MIN, int N_MAX, int Q_MIN, int Q_MAX)
        : N_MIN(N_MIN)
        , N_MAX(N_MAX)
        , Q_MIN(Q_MIN)
        , Q_MAX(Q_MAX)
    {
    }
};

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    Settings small(10, 30, 100, 500), large(10000, MAX_N, 20000, MAX_Q), max(MAX_N, MAX_N, MAX_Q, MAX_Q);
    auto random = [&](const string name, const Settings& settings) {
        int N = rnd.next(settings.N_MIN, settings.N_MAX);
        int Q = rnd.next(settings.Q_MIN, settings.Q_MAX);
        string S = rnd.next("[a-z]{" + to_string(N) + "}");
        vector<pair<int, int>> LR;
        for (int i = 0; i < Q; i++) {
            int l = rnd.next(1, N);
            int r = rnd.next(1, N);
            if (l > r)
                swap(l, r);
            LR.emplace_back(l, r);
        }
        gen(name, S, LR);
    };
    // sample
    // {
    //     gen("00_sample_01.in", "abaaab", vector<pair<int, int>>({ { 1, 6 }, { 1, 4 } }));
    //     gen("00_sample_02.in", "ababababab", vector<pair<int, int>>({ { 1, 10 }, { 1, 6 } }));
    //     gen("00_sample_03.in", "abababababababababab", vector<pair<int, int>>({ { 1, 20 }, { 1, 16 } }));
    // }
    // small
    {
        // random
        for (int i = 0; i < 10; i++) {
            random(format("10_small_{}.in", i + 1), small);
        }
    }
    // large
    {
        // random
        for (int i = 0; i < 10; i++) {
            random(format("20_large_{}.in", i + 1), large);
        }
    }
    // max
    {
        // random
        for (int i = 0; i < 10; i++) {
            random(format("30_max_{}.in", i + 1), max);
        }
    }
    return 0;
}