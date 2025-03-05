#include "testlib.h"
#include "bits/stdc++.h"
#include "constraints.hpp"
#include <filesystem>

using namespace std;

void generate(const string name, const string S, const vector<pair<int, int>> LR)
{
    ofstream ofs(name);
    ofs << S.size() << " " << LR.size() << endl;
    ofs << S << endl;
    for (auto [l, r] : LR) {
        ofs << l << " " << r << endl;
    }
}

struct Generator{
    function<int()> N_gen, Q_gen;
    function<string(int)> S_gen;
    function<vector<pair<int, int>>(int, int)> LR_gen;
    Generator(function<int()> N_gen, function<int()> Q_gen, function<string(int)> S_gen, function<vector<pair<int, int>>(int, int)> LR_gen)
        : N_gen(N_gen)
        , Q_gen(Q_gen)
        , S_gen(S_gen)
        , LR_gen(LR_gen)
    {
    }
    void generateTestFile(const string name) {
        int N = N_gen();
        int Q = Q_gen();
        string S = S_gen(N);
        vector<pair<int, int>> LR = LR_gen(N, Q);
        generate(name, S, LR);
    }
};

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
    auto N_small = [&](){ return rnd.next(MIN_N, 100ll); };
    auto N_random = [&](){ return rnd.next(MIN_N, MAX_N); };
    auto N_max = [&](){ return rnd.next(MAX_N, MAX_N); };
    auto Q_small = [&](){ return rnd.next(MIN_Q, 100ll); };
    auto Q_random = [&](){ return rnd.next(MIN_Q, MAX_Q); };
    auto Q_max = [&](){ return rnd.next(MAX_Q, MAX_Q); };
    auto S_random = [&](int N){ return rnd.next("[a-z]{" + to_string(N) + "}"); };
    auto S_few_alphabets = [&](int N){ return rnd.next("[ac]{" + to_string(N) + "}"); };
    auto S_few_random = [&](int N){
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        int num_chars = rnd.next(2, 4);
        set<char> char_set;
        while (char_set.size() < num_chars) {
            char_set.insert(alphabet[rnd.next(0, 25)]);
        }
        string chars(char_set.begin(), char_set.end());
        return rnd.next("[" + chars + "]{" + to_string(N) + "}");
    };
    auto S_alternating = [&](int N){
        char c1 = 'a' + rnd.next(0, 25);
        char c2;
        do {
            c2 = 'a' + rnd.next(0, 25);
        } while (c1 == c2);
        string S;
        for (int i = 0; i < N; i++) {
            S += (i % 2 == 0) ? c1 : c2;
        }
        return S;
    };

    auto S_all_same = [&](int N){
        char c = 'a' + rnd.next(0, 25);
        return string(N, c);
    };
    auto LR_random = [&](int N, int Q){
        vector<pair<int, int>> res;
        for (int i = 0; i < Q; i++) {
            int L = rnd.next(1, N), R = rnd.next(1, N);
            if (L > R) swap(L, R);
            res.emplace_back(L, R);
        }
        return res;
    };
    auto LR_large_range = [&](int N, int Q){
        vector<pair<int, int>> res;
        queue<pair<int, int>> que;
        set<pair<int, int>> used;
        que.push({1, N});
        used.insert({1, N});
        while (!que.empty() && res.size() < Q) {
            auto [L, R] = que.front();
            que.pop();
            res.emplace_back(L, R);
            if(L < R){
                if(!used.contains({L + 1, R})){
                    que.push({L + 1, R});
                    used.insert({L + 1, R});
                }
                if(!used.contains({L, R - 1})){
                    que.push({L, R - 1});
                    used.insert({L, R - 1});
                }
            }
        }
        return res;
    };
    // small
    {
        // random
        Generator small(N_small, Q_small, S_random, LR_random);
        for (int i = 0; i < 5; i++) {
            small.generateTestFile(::format("10_small_%02d.in", i + 1));
        }
    }
    // large
    {
        // random
        Generator large(N_random, Q_random, S_random, LR_random);
        for (int i = 0; i < 5; i++) {
            large.generateTestFile(::format("20_large_%02d.in", i + 1));
        }
    }
    // max
    {
        // random
        Generator max_case(N_max, Q_max, S_random, LR_large_range);
        for (int i = 0; i < 10; i++) {
            max_case.generateTestFile(::format("30_max_%02d.in", i + 1));
        }
    }
    // アルファベットの種類が少ないケース
    {
        Generator few_alphabets(N_max, Q_max, S_few_random, LR_large_range);
        for (int i = 0; i < 10; i++) {
            few_alphabets.generateTestFile(::format("40_few_alphabets_%02d.in", i + 1));
        }
    }
    // min
    {
        Generator min_case([](){ return MIN_N; }, [](){ return MIN_Q; }, S_random, LR_random);
        for (int i = 0; i < 5; i++) {
            min_case.generateTestFile(::format("50_min_%02d.in", i + 1));
        }
    }
    // 交互
    {
        Generator alternating_case(N_max, Q_max, S_alternating, LR_large_range);
        for (int i = 0; i < 10; i++) {
            alternating_case.generateTestFile(::format("60_alternating_%02d.in", i + 1));
        }
    }
    // 全て同じ文字のケース
    {
        Generator all_same_case(N_max, Q_max, S_all_same, LR_large_range);
        for (int i = 0; i < 5; i++) {
            all_same_case.generateTestFile(::format("70_all_same_%02d.in", i + 1));
        }
    }
    return 0;
}