#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MIN_N = 1;
const int MAX_N = 200000;
const int MIN_A = 1;
const int MAX_A = 1000000000;
const int MIN_H = 1;
const int MAX_H = 1000000000;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);
    /**
     * Input
     * N
     */
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readEoln();
    /**
     * Input
     * A1 H1
     * A2 H2
     * ...
     * An Hn
     */
    vector<int> A(N), H(N);
    for (int i = 0; i < N; i++)
    {
        A[i] = inf.readInt(MIN_A, MAX_A, "A");
        inf.readSpace();
        H[i] = inf.readInt(MIN_H, MAX_H, "H");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
