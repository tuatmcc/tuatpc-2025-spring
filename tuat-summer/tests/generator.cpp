#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MIN_N = 1;
const int MAX_N = 2e5;
const ll MIN_A = 1;
const ll MAX_A = 1e9;
const ll MIN_H = 1;
const ll MAX_H = 1e9;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    for(int t = 0; t < 3; t++){
        for(int i = 0; i < 2; i++){
            ofstream of(format("02_123_%02d.in", 2 * t + i).c_str());
            int n = t + 1;
            of << n << endl;
            for(int i = 0; i < n; i++){
                of << rnd.next(MIN_A, MAX_A) << " ";
                of << rnd.next(MIN_H, MAX_H) << endl;
            }
            of.close();
        }
    }
    ofstream of(format("02_handmade.in").c_str());
    of << 3 << endl;
    of << "1600 1400" << endl;
    of << "1200 1600" << endl;
    of << "1000 400" << endl;
    of.close();
    for (int t = 0; t < 10; t++) {
        ofstream of(format("02_random_%02d.in", t+1).c_str());
        int n = rnd.next(MIN_N, MAX_N);
        of << n << endl;
        for(int i = 0; i < n; i++){
            of << rnd.next(MIN_A, MAX_A) << " ";
            of << rnd.next(MIN_H, MAX_H) << endl;
        }
        of.close();
    }
    return 0;
}