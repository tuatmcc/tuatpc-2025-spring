#include <bits/stdc++.h>
#include "testlib.h"
#include "constraints.h"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readEoln();
    auto A = inf.readInts(N, MIN_A, MAX_A, "A");
    inf.readEoln();
    auto B = inf.readInts(N, MIN_A, MAX_A, "B");
    inf.readEoln();
    inf.readEof();
    return 0;
}