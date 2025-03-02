#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MIN_N = 1;
const int MAX_N = 200000;
const int MIN_A = 1;
const int MAX_A = 1000000000;
const int MIN_B = 1;
const int MAX_B = 1000000000;

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
     * A_1 A_2 ... A_N
     * B_1 B_2 ... B_N
     */
    vector<int> A(N), B(N);
    A = inf.readInts(N, MIN_A, MAX_A, "A");
    inf.readEoln();
    B = inf.readInts(N, MIN_B, MAX_B, "B");
    inf.readEoln();


    inf.readEof();
    return 0;
}
