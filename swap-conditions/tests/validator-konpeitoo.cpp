#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int MIN_X = 1;
const int MAX_X = 4;
const long long MIN_A = -1000000000000000000;
const long long MAX_A = 1000000000000000000;
const int MIN_T = 1;
const int MAX_T = 100000;

int main(int argc, char *argv[]){
    registerValidation(argc, argv);
    int T = inf.readInt(MIN_T, MAX_T, "T");
    inf.readEoln();
    for(int t = 0; t < T; t++){
        int X = inf.readInt(MIN_X, MAX_X, format("X(%d)", t + 1).c_str());
        inf.readSpace();
        int Y = inf.readInt(MIN_X, MAX_X, format("Y(%d)", t + 1).c_str());
        ensuref(X != Y, "X and Y are duplicates");
        inf.readSpace();
        int R = inf.readInt(MIN_X, MAX_X, format("R(%d)", t + 1).c_str());
        inf.readEoln();
        for(int i = 0; i < 4; i++){
            if(i != 0)inf.readSpace();
            inf.readLong(MIN_A, MAX_A, format("A(%d, %d)", t + 1, i + 1).c_str());
        }
        inf.readEoln();
    }
    inf.readEof();
}