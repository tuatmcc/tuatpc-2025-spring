#include <bits/stdc++.h>
#include "testlib.h"
#include "constraints.h"
using namespace std;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    
    // case 00 ... sample
    {
        ofstream of(format("00_sample_01.in").c_str());
        of << "4" << endl;
        of << "100 500" << endl;
        of << "1100 200" << endl;
        of << "4300 2350" << endl;
        of << "1200 1700" << endl;
        of.close();
    }
    {
        ofstream of(format("00_sample_02.in").c_str());
        of << "5" << endl;
        of << "314 159" << endl;
        of << "265 358" << endl;
        of << "979 323" << endl;
        of << "846 264" << endl;
        of << "338 327" << endl;
        of.close();
    }
    {
        ofstream of(format("00_sample_03.in").c_str());
        of << "9" << endl; // check 2025-01-29
        of << "1264 1297" << endl; // ngng628
        of << "1862 1278" << endl; // new_textfile
        of << "1748 1230" << endl; // lX57
        of << "1286 1357" << endl; // sunrize
        of << "972 891" << endl; // Sakasu
        of << "891 7" << endl; // sugawa197203
        of << "860 1309" << endl; // mr63tnegi
        of << "1337 1407" << endl; // toufu24
        of << "958 240" << endl; // shojusen
        of.close();
    }

    const int RATE_MAX = 1600;
    const int SUM_MAX = 4200;

    // 1* ... test
    // 10 ... random
    // type 1 ... All Participant's Both Rate < 1600
    for(int t = 1; t <= 5; ++t){
        ofstream of(format("10_random_%02d.in", t).c_str());
        int RND_MIN_N = MAX_N * 0.8;
        int RND_MAX_N = MAX_N * 0.9;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        of << N << endl;
        for(int i = 0; i < N; ++i){
            int A = rnd.next(MIN_A, RATE_MAX - 1);
            int B = rnd.next(MIN_H, RATE_MAX - 1);
            of << A << ' ' << B << endl;
        }
        of.close();
    }
    // type 2 ... All Participant's Each Rate >= 1600
    for(int t = 6; t <= 10; ++t){
        ofstream of(format("10_random_%02d.in", t).c_str());
        int RND_MIN_N = MAX_N * 0.8;
        int RND_MAX_N = MAX_N * 0.9;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        of << N << endl;
        for(int i = 0; i < N; ++i){
            int A = rnd.next(MIN_A, RATE_MAX - 1);
            int B = rnd.next(MIN_H, RATE_MAX - 1);
            if(rnd.next(0, 1)) A = rnd.next(RATE_MAX, MAX_A);
            else B = rnd.next(RATE_MAX, MAX_H);
            of << A << ' ' << B << endl;
        }
        of.close();
    }
    // type 3 ... All Participant's Both Rate >= 1600
    for(int t = 11; t <= 15; ++t){
        ofstream of(format("10_random_%02d.in", t).c_str());
        int RND_MIN_N = MAX_N * 0.8;
        int RND_MAX_N = MAX_N * 0.9;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        of << N << endl;
        for(int i = 0; i < N; ++i){
            int A = rnd.next(RATE_MAX, MAX_A);
            int B = rnd.next(RATE_MAX, MAX_H);
            of << A << ' ' << B << endl;
        }
        of.close();
    }
    // 11 ... max
    for(int t = 1; t <= 3; ++t){
        ofstream of(format("11_max_%02d.in", t).c_str());
        int N = MAX_N;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << rnd.next(MIN_A, SUM_MAX - 1) << ' ' << rnd.next(MIN_H, SUM_MAX - 1) << endl;
        }
        of.close();
    }
    for(int t = 4; t <= 4; ++t){
        ofstream of(format("11_max_%02d.in", t).c_str());
        int N = MAX_N;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << MIN_A << ' ' << MIN_H << endl;
        }
        of.close();
    }
    for(int t = 5; t <= 5; ++t){
        ofstream of(format("11_max_%02d.in", t).c_str());
        int N = SUM_MAX;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << MIN_A << ' ' << MIN_H << endl;
        }
        of.close();
    }
    for(int t = 6; t <= 6; ++t){
        ofstream of(format("11_max_%02d.in", t).c_str());
        int N = SUM_MAX + 1;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << MIN_A << ' ' << MIN_H << endl;
        }
        of.close();
    }

    // 2* ... subtask
    // 20 ... random
    // type 1 ... All Participant's Both Rate < 1600
    for(int t = 1; t <= 5; ++t){
        ofstream of(format("20_random_%02d.in", t).c_str());
        int RND_MIN_N = MAX_SUBTASK_N * 0.8;
        int RND_MAX_N = MAX_SUBTASK_N * 0.9;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        of << N << endl;
        for(int i = 0; i < N; ++i){
            int A = rnd.next(MIN_A, RATE_MAX - 1);
            int B = rnd.next(MIN_H, RATE_MAX - 1);
            of << A << ' ' << B << endl;
        }
        of.close();
    }
    // type 2 ... All Participant's Each Rate >= 1600
    for(int t = 6; t <= 10; ++t){
        ofstream of(format("20_random_%02d.in", t).c_str());
        int RND_MIN_N = MAX_SUBTASK_N * 0.8;
        int RND_MAX_N = MAX_SUBTASK_N * 0.9;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        of << N << endl;
        for(int i = 0; i < N; ++i){
            int A = rnd.next(MIN_A, RATE_MAX - 1);
            int B = rnd.next(MIN_H, RATE_MAX - 1);
            if(rnd.next(0, 1)) A = rnd.next(RATE_MAX, MAX_A);
            else B = rnd.next(RATE_MAX, MAX_H);
            of << A << ' ' << B << endl;
        }
        of.close();
    }
    // type 3 ... All Participant's Both Rate >= 1600
    for(int t = 11; t <= 15; ++t){
        ofstream of(format("20_random_%02d.in", t).c_str());
        int RND_MIN_N = MAX_SUBTASK_N * 0.8;
        int RND_MAX_N = MAX_SUBTASK_N * 0.9;
        int N = rnd.next(RND_MIN_N, RND_MAX_N);
        of << N << endl;
        for(int i = 0; i < N; ++i){
            int A = rnd.next(RATE_MAX, MAX_A);
            int B = rnd.next(RATE_MAX, MAX_H);
            of << A << ' ' << B << endl;
        }
        of.close();
    }
    // 21 ... max
    for(int t = 1; t <= 3; ++t){
        ofstream of(format("21_max_%02d.in", t).c_str());
        int N = MAX_SUBTASK_N;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << rnd.next(MIN_A, SUM_MAX - 1) << ' ' << rnd.next(MIN_H, SUM_MAX - 1) << endl;
        }
        of.close();
    }
    for(int t = 4; t <= 4; ++t){
        ofstream of(format("21_max_%02d.in", t).c_str());
        int N = MAX_SUBTASK_N;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << MIN_A << ' ' << MIN_H << endl;
        }
        of.close();
    }
    // 22 ... min
    for(int t = 1; t <= 3; ++t){
        ofstream of(format("22_min_%02d.in", t).c_str());
        int N = MIN_N;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << rnd.next(MIN_A, SUM_MAX - 1) << ' ' << rnd.next(MIN_H, SUM_MAX - 1) << endl;
        }
        of.close();
    }
    // 29 ... hand
    {
        ofstream of("29_hand_01.in");
        int N = MAX_SUBTASK_N;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << RATE_MAX - 1 << ' ' << RATE_MAX - 1 << endl;
        }
        of.close();
    }
    {
        ofstream of("29_hand_02.in");
        int N = MAX_SUBTASK_N;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << RATE_MAX << ' ' << RATE_MAX << endl;
        }
        of.close();
    }
    {
        ofstream of("29_hand_03.in");
        int N = MAX_SUBTASK_N;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << SUM_MAX - 1 << ' ' << SUM_MAX - 1 << endl;
        }
        of.close();
    }
    {
        ofstream of("29_hand_04.in");
        int N = MAX_SUBTASK_N;
        of << N << endl;
        for(int i = 0; i < N; ++i){
            of << SUM_MAX << ' ' << SUM_MAX << endl;
        }
        of.close();
    }

    return 0;
}