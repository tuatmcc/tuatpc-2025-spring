#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MIN_KJ = 1;
const int MAX_KJ = 4;
const ll MIN_A = -1e18;
const ll MAX_A = 1e18;
const ll MIN_H = 1;
const ll MAX_H = 1e9;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    for (int t = 0; t < 10; t++) {
        ofstream of(format("02_random_%02d.in", t+1).c_str());
        vector<int> v = {1, 2, 3, 4}, kj;
        for(int i = 0; i < 4; i++){
            int t = rnd.next(0, 3 - i);
            kj.push_back(v[t]);
            v.erase(v.begin() + t);
        }
        of << kj[0] << " ";
        for(int i = 0; i < 4; i++){
            of << rnd.next(MIN_A, MAX_A);
            if(i == 3) of << endl;
            else of << " ";
        }
        for(int i = 1; i < 4; i++){
            of << kj[i];
            if(i == 3) of << endl;
            else of << " ";
        }
        of.close();
    }
    return 0;
}