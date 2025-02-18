#include <bits/stdc++.h>
#include "testlib.h"
#include "constraints.h"

using namespace std;

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);
    const int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readEoln();
    for (int i = 0; i < N; i++) {
        const int A_i = inf.readInt(MIN_A, MAX_A, "A_i");
        inf.readSpace();
        const int H_i = inf.readInt(MIN_H, MAX_H, "H_i");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}