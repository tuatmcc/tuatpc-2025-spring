#include "testlib.h"
#include "bits/stdc++.h"
#include "constraints.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);
    const int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    const int Q = inf.readInt(MIN_Q, MAX_Q, "Q");
    inf.readEoln();
    string S = inf.readString("[a-z]{" + to_string(N) + "}", "S");
    assert(N == S.size());
    for (int i = 0; i < Q; i++) {
        const int L_i = inf.readInt(1, N, "L_i");
        inf.readSpace();
        const int R_i = inf.readInt(1, N, "R_i");
        assert(L_i <= R_i);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}