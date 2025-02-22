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
    sample1 << "1 4\n800 1000 2000 4000\n";
    sample1.close();
    ofstream sample2(format("04_sample_2.in").c_str());
    sample2 << "3 2\n25000 25000 25000 25000\n";
    sample2.close();
    ofstream sample3(format("04_sample_3.in").c_str());
    sample3 << "2 4\n17000 12000 21000 60000\n";
    sample3.close();
    //random
    for (int t = 0; t < 10; t++) {
        ofstream of(format("04_random_%02d.in", t+1).c_str());
        vector<int> v = {1, 2, 3, 4};
        int k, j;
        int u = rnd.next(0, 3);
        k = v[u];
        v.erase(v.begin() + u);
        u = rnd.next(0, 2);
        j = v[u];
        of << k << " " << j << endl;
        for(int i = 0; i < 4; i++){
            of << rnd.next(MIN_A, MAX_A);
            if(i == 3) of << endl;
            else of << " ";
        }
        of.close();
    }
    //tokoko needs huge point to swap
    for (int t = 0; t < 5; t++) {
        ofstream of(format("04_random-huge_%02d.in", t+1).c_str());
        vector<int> v = {1, 2, 3, 4};
        int k, j;
        int u = rnd.next(0, 3);
        k = v[u];
        v.erase(v.begin() + u);
        u = rnd.next(0, 2);
        j = v[u];
        of << k << " " << j << endl;
        for(int i = 0; i < 4; i++){
            if(i == k - 1) of << rnd.next((ll)-1e18, (ll)-95e16);
            else of << rnd.next((ll)95e16, (ll)1e18);
            if(i == 3) of << endl;
            else of << " ";
        }
        of.close();
    }
    //tokoko and friends have same points if tokoko select the S.
    for (int t = 0; t < 10; t++) {
        ofstream of(format("04_random_tie_%02d.in", t+1).c_str());
        vector<int> v = {1, 2, 3, 4};
        int k, j;
        int u = rnd.next(0, 3);
        k = v[u];
        v.erase(v.begin() + u);
        u = rnd.next(0, 2);
        j = v[u];
        of << k << " " << j << endl;
        ll tokoko = rnd.next(MIN_A, (ll)2e17);
        ll steal = rnd.next((ll)0, (ll)4e17);

        for(int i = 0; i < 4; i++){
            if(i == k - 1) of << tokoko;
            else if(i == j - 1) of << tokoko + 2 * steal;
            else of << steal;
            if(i == 3) of << endl;
            else of << " ";
        }
        of.close();
    }
    ofstream of(format("04_max.in").c_str());
    vector<int> v = {1, 2, 3, 4};
    int k, j;
    int u = rnd.next(0, 3);
    k = v[u];
    v.erase(v.begin() + u);
    u = rnd.next(0, 2);
    j = v[u];
    of << k << " " << j << endl;
    ll tokoko = MAX_A;
    for(int i = 0; i < 4; i++){
        of << tokoko;
        if(i == 3) of << endl;
        else of << " ";
    }
    of.close();


    ofstream of2(format("04_min.in").c_str());
    v = {1, 2, 3, 4};
    u = rnd.next(0, 3);
    k = v[u];
    v.erase(v.begin() + u);
    u = rnd.next(0, 2);
    j = v[u];
    of2 << k << " " << j << endl;
    tokoko = -MAX_A;
    for(int i = 0; i < 4; i++){
        of2 << tokoko;
        if(i == 3) of2 << endl;
        else of2 << " ";
    }
    of2.close();
    return 0;
}