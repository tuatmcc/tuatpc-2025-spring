#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int MIN_N = 1;
const int MAX_N = 500000;
const int MIN_M = 1;
const int MIN_W = 1;
const int MAX_W = 100;
const int MIN_L = 1;
const int MAX_L = 8;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);
    /**
     * N
     * X1 X2 ... XN
     */

    int n = inf.readInt(MIN_N, MAX_N, "n");
    inf.readEoln();
    vector<string> x = inf.readTokens(n, format("[A-G]{1,1}"));
    inf.readEoln();

    /**
     * M1
     * V1 V2 ... VM1
     * W1 W2 ... WM1
     * M2
     * V1 V2 ... VM2
     * W1 W2 ... WM2
     * ...
     * MN
     * V1 V2 ... VMN
     * W1 W2 ... WMN
     */

    vector<int> m(n);
    int sum_m = 0;

    for (int i = 0; i < n; i++)
    {
        m[i] = inf.readInt(MIN_M, min(n, 100), "m");
        sum_m += m[i];
        inf.readEoln();
        vector<int> v = inf.readInts(m[i], 1, n, "v");
        for (int j = 1; j < m[i]; j++)
        {
            ensuref(v[j - 1] < v[j], "v%d is not sorted", i + 1);
        }
        inf.readEoln();
        vector<int> w = inf.readInts(m[i], MIN_W, MAX_W, "w");
        int sum_w = 0;
        for (int j = 0; j < m[i]; j++)
        {
            sum_w += w[j];
        }
        ensuref(sum_w <= 1000, "sum of w%d is too large", i + 1);
        inf.readEoln();
    }

    ensuref((long long)sum_m <= min((long long)n * n, (long long)100000), "sum of m is too large");

    int l = inf.readInt(MIN_L, MAX_L, "l");
    inf.readEoln();
    string s = inf.readToken(format("[A-G]{%d,%d}", l, l));
    inf.readEoln();

    inf.readEof();

    return 0;
}