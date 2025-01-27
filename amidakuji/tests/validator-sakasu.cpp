#include "testlib.h"
#include "constraints.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    int M = inf.readInt(MIN_M, MAX_M, "M");
    inf.readEoln();
    int Q = inf.readInt(MIN_Q, MAX_Q, "Q");
    inf.readEoln();

    vector<vector<bool>> lines(M, vector<bool>(N - 1, false));
    while (Q--)
    {
        int t = inf.readInt(1, 3, "t");
        inf.readSpace();
        if (t == 1)
        {
            int x = inf.readInt(1, N - 1, "x");
            inf.readSpace();
            int y = inf.readInt(1, M, "y");
            inf.readEoln();
            --x, --y;
            ensuref(!lines[y][x], "line already exists");
            if (x > 0)
                ensuref(!lines[y][x - 1], "line already exists left");
            if (x < N - 2)
                ensuref(!lines[y][x + 1], "line already exists right");
            lines[y][x] = true;
        }
        else if (t == 2)
        {
            int x = inf.readInt(1, N - 1, "x");
            inf.readSpace();
            int y = inf.readInt(1, M, "y");
            inf.readEoln();
            x--, y--;
            assert(lines[y][x]);
            lines[y][x] = false;
        }
        else
        {
            int s = inf.readInt(1, N, "s");
            inf.readEoln();
        }
    }
    inf.readEof();
}
