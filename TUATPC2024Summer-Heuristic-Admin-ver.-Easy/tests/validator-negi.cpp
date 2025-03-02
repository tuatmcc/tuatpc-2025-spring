#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int MIN_N = 1;
const int MAX_N = 2e5;
const ll MIN_A = 1;
const ll MAX_A = 1e9;
const ll MIN_B = 1;
const ll MAX_B = 1e9;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int n = inf.readInt(MIN_N, MAX_N, "N");
    inf.readEoln();
    for(int i = 0; i < n; i++){
        inf.readLong(MIN_A, MAX_A, "A");
        if(i == n - 1) inf.readEoln();
        else inf.readSpace();
    }
    for(int i = 0; i < n; i++){
        inf.readLong(MIN_B, MAX_B, "B");
        if(i == n - 1) inf.readEoln();
        else inf.readSpace();
    }
    inf.readEof();
    return 0;
}