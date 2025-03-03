#include <bits/stdc++.h>
#include "testlib.h"
#include "constraints.h"
using namespace std;

void print(const string case_name, int N, const vector<int> &A, const vector<int> &B){
    ofstream of(case_name.c_str());
    of << N << '\n';
    for(int i = 0; i < N; ++i){
        of << A[i] << " \n"[i + 1 == N];
    }
    for(int i = 0; i < N; ++i){
        of << B[i] << " \n"[i + 1 == N];
    }
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    
    // case 00 ... sample
    {
        int N = 4;
        vector<int> A{100, 1100, 4300, 1200};
        vector<int> B{500, 200, 2350, 1700};
        print(format("00_sample_01.in"), N, A, B);
    }
    {
        int N = 5;
        vector<int> A{314, 159, 265, 358, 979};
        vector<int> B{323, 846, 264, 338, 327};
        print(format("00_sample_02.in"), N, A, B);
    }
    {
        int N = 9;
        vector<int> A{1264, 1862, 1748, 1286, 972, 891, 860, 1337, 958};
        vector<int> B{1297, 1278, 1230, 1357, 891, 7, 1309, 1407, 240};
        print(format("00_sample_03.in"), N, A, B);
    }

    const int RATE_MAX = 1600;
    const int SUM_MAX = 4200;
    const int RATE_SMALL = 160;

    const vector<int> RANDOM_CASE{10, 5, 5, 3};
    auto RANDOM_CASE_START = [&](int type) -> int {
        int ret = 1;
        for(int i = 0; i < type; ++i) ret += RANDOM_CASE[i];
        return ret;
    };
    auto RANDOM_CASE_END = [&](int type) -> int {
        int ret = 1;
        for(int i = 0; i <= type; ++i) ret += RANDOM_CASE[i];
        return ret;
    };
    const vector<int> MAX_CASE{3, 3, 3, 3};
    auto MAX_CASE_START = [&](int type) -> int {
        int ret = 1;
        for(int i = 0; i < type; ++i) ret += MAX_CASE[i];
        return ret;
    };
    auto MAX_CASE_END = [&](int type) -> int {
        int ret = 1;
        for(int i = 0; i <= type; ++i) ret += MAX_CASE[i];
        return ret;
    };
    // Type 0 ... どちらのレートも 160 未満
    // Type 1 ... どちらのレートも 1600 未満
    // Type 2 ... どちらのレートも 1600 以上 4200 未満
    // Type 3 ... どちらのレートも 4200 以上

    // 1* ... subtask
    // 10 ... random
    for(int t = RANDOM_CASE_START(0); t <= RANDOM_CASE_END(0); ++t){
        int RND_MIN_N = MAX_SUBTASK_N * 0.90;
        int RND_MAX_N = MAX_SUBTASK_N * 0.95;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(MIN_A, RATE_SMALL - 1));
            B.emplace_back(rnd.next(MIN_B, RATE_SMALL - 1));
        }
        print(format("10_subtask_random_%02d.in", t), N, A, B);
    }
    for(int t = RANDOM_CASE_START(1); t <= RANDOM_CASE_END(1); ++t){
        int RND_MIN_N = MAX_SUBTASK_N * 0.90;
        int RND_MAX_N = MAX_SUBTASK_N * 0.95;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(MIN_A, RATE_MAX - 1));
            B.emplace_back(rnd.next(MIN_B, RATE_MAX - 1));
        }
        print(format("10_subtask_random_%02d.in", t), N, A, B);
    }
    for(int t = RANDOM_CASE_START(2); t <= RANDOM_CASE_END(2); ++t){
        int RND_MIN_N = MAX_SUBTASK_N * 0.90;
        int RND_MAX_N = MAX_SUBTASK_N * 0.95;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(RATE_MAX, SUM_MAX - 1));
            B.emplace_back(rnd.next(RATE_MAX, SUM_MAX - 1));
        }
        print(format("10_subtask_random_%02d.in", t), N, A, B);
    }
    for(int t = RANDOM_CASE_START(3); t <= RANDOM_CASE_END(3); ++t){
        int RND_MIN_N = MAX_SUBTASK_N * 0.90;
        int RND_MAX_N = MAX_SUBTASK_N * 0.95;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(SUM_MAX, MAX_A));
            B.emplace_back(rnd.next(SUM_MAX, MAX_B));
        }
        print(format("10_subtask_random_%02d.in", t), N, A, B);
    }

    // 2* ... main
    // 20 ... random
    for(int t = RANDOM_CASE_START(0); t <= RANDOM_CASE_END(0); ++t){
        int RND_MIN_N = MAX_N * 0.90;
        int RND_MAX_N = MAX_N * 0.95;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(MIN_A, RATE_SMALL - 1));
            B.emplace_back(rnd.next(MIN_B, RATE_SMALL - 1));
        }
        print(format("20_main_random_%02d.in", t), N, A, B);
    }
    for(int t = RANDOM_CASE_START(1); t <= RANDOM_CASE_END(1); ++t){
        int RND_MIN_N = MAX_N * 0.90;
        int RND_MAX_N = MAX_N * 0.95;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(MIN_A, RATE_MAX - 1));
            B.emplace_back(rnd.next(MIN_B, RATE_MAX - 1));
        }
        print(format("20_main_random_%02d.in", t), N, A, B);
    }
    for(int t = RANDOM_CASE_START(2); t <= RANDOM_CASE_END(2); ++t){
        int RND_MIN_N = MAX_N * 0.90;
        int RND_MAX_N = MAX_N * 0.95;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(RATE_MAX, SUM_MAX - 1));
            B.emplace_back(rnd.next(RATE_MAX, SUM_MAX - 1));
        }
        print(format("20_main_random_%02d.in", t), N, A, B);
    }
    for(int t = RANDOM_CASE_START(3); t <= RANDOM_CASE_END(3); ++t){
        int RND_MIN_N = MAX_N * 0.90;
        int RND_MAX_N = MAX_N * 0.95;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(SUM_MAX, MAX_A));
            B.emplace_back(rnd.next(SUM_MAX, MAX_B));
        }
        print(format("20_main_random_%02d.in", t), N, A, B);
    }

    // 30 ... min
    {
        int N = MIN_N;
        vector<int> A{1};
        vector<int> B{1};
        print(format("30_min_01.in"), N, A, B);
    }
    {
        int N = MIN_N;
        vector<int> A{RATE_MAX - 1};
        vector<int> B{RATE_MAX - 1};
        print(format("30_min_02.in"), N, A, B);
    }
    {
        int N = MIN_N;
        vector<int> A{RATE_MAX};
        vector<int> B{RATE_MAX};
        print(format("30_min_03.in"), N, A, B);
    }
    {
        int N = MIN_N;
        vector<int> A{SUM_MAX - 1};
        vector<int> B{SUM_MAX - 1};
        print(format("30_min_04.in"), N, A, B);
    }
    {
        int N = MIN_N;
        vector<int> A{SUM_MAX};
        vector<int> B{SUM_MAX};
        print(format("30_min_05.in"), N, A, B);
    }
    {
        int N = MIN_N;
        vector<int> A{MAX_A};
        vector<int> B{MAX_B};
        print(format("30_min_06.in"), N, A, B);
    }

    // 40 ... subtask max
    for(int t = MAX_CASE_START(0); t <= MAX_CASE_END(0); ++t){
        int N = MAX_SUBTASK_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(MIN_A, RATE_SMALL - 1));
            B.emplace_back(rnd.next(MIN_B, RATE_SMALL - 1));
        }
        print(format("40_subtask_max_%02d.in", t), N, A, B);
    }
    for(int t = MAX_CASE_START(1); t <= MAX_CASE_END(1); ++t){
        int N = MAX_SUBTASK_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(MIN_A, RATE_MAX - 1));
            B.emplace_back(rnd.next(MIN_B, RATE_MAX - 1));
        }
        print(format("40_subtask_max_%02d.in", t), N, A, B);
    }
    for(int t = MAX_CASE_START(2); t <= MAX_CASE_END(2); ++t){
        int N = MAX_SUBTASK_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(RATE_MAX, SUM_MAX - 1));
            B.emplace_back(rnd.next(RATE_MAX, SUM_MAX - 1));
        }
        print(format("40_subtask_max_%02d.in", t), N, A, B);
    }
    for(int t = MAX_CASE_START(3); t <= MAX_CASE_END(3); ++t){
        int N = MAX_SUBTASK_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(SUM_MAX, MAX_A));
            B.emplace_back(rnd.next(SUM_MAX, MAX_B));
        }
        print(format("40_subtask_max_%02d.in", t), N, A, B);
    }

    // 41 ... main max
    for(int t = MAX_CASE_START(0); t <= MAX_CASE_END(0); ++t){
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(MIN_A, RATE_SMALL - 1));
            B.emplace_back(rnd.next(MIN_B, RATE_SMALL - 1));
        }
        print(format("41_main_max_%02d.in", t), N, A, B);
    }
    for(int t = MAX_CASE_START(1); t <= MAX_CASE_END(1); ++t){
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(MIN_A, RATE_MAX - 1));
            B.emplace_back(rnd.next(MIN_B, RATE_MAX - 1));
        }
        print(format("41_main_max_%02d.in", t), N, A, B);
    }
    for(int t = MAX_CASE_START(2); t <= MAX_CASE_END(2); ++t){
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(RATE_MAX, SUM_MAX - 1));
            B.emplace_back(rnd.next(RATE_MAX, SUM_MAX - 1));
        }
        print(format("41_main_max_%02d.in", t), N, A, B);
    }
    for(int t = MAX_CASE_START(3); t <= MAX_CASE_END(3); ++t){
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(rnd.next(SUM_MAX, MAX_A));
            B.emplace_back(rnd.next(SUM_MAX, MAX_B));
        }
        print(format("41_main_max_%02d.in", t), N, A, B);
    }

    // 90 ... hand
    {
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(MIN_A);
            B.emplace_back(MIN_B);
        }
        print(format("90_hand_01.in"), N, A, B);
    }
    {
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(MAX_A);
            B.emplace_back(MAX_B);
        }
        print(format("90_hand_02.in"), N, A, B);
    }
    {
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(RATE_MAX - 1);
            B.emplace_back(RATE_MAX - 1);
        }
        print(format("90_hand_03.in"), N, A, B);
    }
    {
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(RATE_MAX);
            B.emplace_back(RATE_MAX);
        }
        print(format("90_hand_04.in"), N, A, B);
    }
    {
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(SUM_MAX - 1);
            B.emplace_back(SUM_MAX - 1);
        }
        print(format("90_hand_05.in"), N, A, B);
    }
    {
        int N = MAX_N;
        vector<int> A, B;
        for(int i = 0; i < N; ++i){
            A.emplace_back(SUM_MAX);
            B.emplace_back(SUM_MAX);
        }
        print(format("90_hand_06.in"), N, A, B);
    }

    return 0;
}