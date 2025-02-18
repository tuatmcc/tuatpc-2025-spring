#include <bits/stdc++.h>
#include "testlib.h"
#include "constraints.h"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readEoln();
    for(int i = 0; i < N; ++i){
        inf.readInt(MIN_A, MAX_A, format("A_%d", i + 1));
        inf.readSpace();
        inf.readInt(MIN_H, MAX_H, format("B_%d", i + 1));
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}