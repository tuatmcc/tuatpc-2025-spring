#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int MIN_XYR = 1;
const int MAX_XYR = 4;
const ll MIN_A = -1e18;
const ll MAX_A = 1e18;
const ll MIN_T = 1;
const ll MAX_T = 1e4;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int t = inf.readInt(MIN_T, MAX_T, "T");
    inf.readEoln();
    for(int i = 0; i < t; i++){
        int x = inf.readInt(MIN_XYR, MAX_XYR, "X");
        inf.readSpace();
        int y = inf.readInt(MIN_XYR, MAX_XYR, "Y");
        inf.readSpace();
        int r = inf.readInt(MIN_XYR, MAX_XYR, "R");
        inf.readEoln();
        assert(x != y);
        for(int i = 0; i < 4; i++){
            inf.readLong(MIN_A, MAX_A, "A");
            if(i == 3)inf.readEoln();
            else inf.readSpace();
        }
    }
    inf.readEof();
    return 0;
}