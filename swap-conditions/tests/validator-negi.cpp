#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int MIN_K = 1;
const int MAX_K = 4;
const ll MIN_A = -1e18;
const ll MAX_A = 1e18;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    vector<ll> kj;
    kj.push_back(inf.readInt(MIN_K, MAX_K, "K"));
    inf.readEoln();
    for(int i = 0; i < 4; i++){
        inf.readLong(MIN_A, MAX_A, "A");
        if(i == 3)inf.readEoln();
        else inf.readSpace();
    }
    for(int i = 1; i < 4; i++){
        kj.push_back(inf.readInt(MIN_K, MAX_K, "J"));
        if(i == 3)inf.readEoln();
        else inf.readSpace();
    }
    sort(kj.begin(), kj.end());
    for(int i = 0; i < 4; i++) assert(kj[i] == i + 1);
    inf.readEof();
    return 0;
}