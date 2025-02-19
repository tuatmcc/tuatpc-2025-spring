#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MIN_KJ = 1;
const int MAX_KJ = 4;
const ll MIN_A = -1e18;
const ll MAX_A = 1e18;


int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    ofstream sample1(format("04_sample_1.in").c_str());
    sample1 << "1\n800 1000 2000 4000\n3 2 4\n";
    sample1.close();
    ofstream sample2(format("04_sample_2.in").c_str());
    sample2 << "3\n25000 25000 25000 25000\n4 1 2\n";
    sample2.close();
    //random
    for (int t = 0; t < 10; t++) {
        ofstream of(format("04_random_%02d.in", t+1).c_str());
        vector<int> v = {1, 2, 3, 4}, kj;
        for(int i = 0; i < 4; i++){
            int t = rnd.next(0, 3 - i);
            kj.push_back(v[t]);
            v.erase(v.begin() + t);
        }
        of << kj[0] << endl;
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
    //tokoko needs huge point to swap
    for (int t = 0; t < 5; t++) {
        ofstream of(format("04_random-huge_%02d.in", t+1).c_str());
        vector<int> v = {1, 2, 3, 4}, kj;
        for(int i = 0; i < 4; i++){
            int t = rnd.next(0, 3 - i);
            kj.push_back(v[t]);
            v.erase(v.begin() + t);
        }
        of << kj[0] << endl;
        for(int i = 0; i < 4; i++){
            if(i == kj[0] - 1) of << rnd.next((ll)-1e18, (ll)-95e16);
            else of << rnd.next((ll)95e16, (ll)1e18);
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
    //tokoko and friends have same points if tokoko select the S.
    for (int t = 0; t < 10; t++) {
        ofstream of(format("04_random_tie_%02d.in", t+1).c_str());
        vector<int> v = {1, 2, 3, 4}, kj;
        for(int i = 0; i < 4; i++){
            int t = rnd.next(0, 3 - i);
            kj.push_back(v[t]);
            v.erase(v.begin() + t);
        }
        of << kj[0] << endl;
        ll tokoko = rnd.next(MIN_A, (ll)2e17);
        ll steal = rnd.next((ll)0, (ll)4e17);

        for(int i = 0; i < 4; i++){
            if(i == kj[0] - 1) of << tokoko;
            else if(i == kj[3] - 1) of << tokoko + 2 * steal;
            else of << steal;
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