#include <bits/stdc++.h>
#include "testlib.h"
#include "constraints.hpp"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    int Q = inf.readInt(MIN_Q, MAX_Q, "Q");
    inf.readEoln();
    string S = inf.readString(format("[a-z]{%d}", N), "S");
    for(int i = 0; i < Q; ++i){
        int l = inf.readInt(1, N, format("l_%d", i + 1));
        inf.readSpace();
        int r = inf.readInt(1, N, format("r_%d", i + 1));
        inf.readEoln();
        assert(l <= r);
    }
    inf.readEof();
}