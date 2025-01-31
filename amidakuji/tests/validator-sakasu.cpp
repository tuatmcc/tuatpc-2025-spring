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

    set<pair<int, int>> lines;
    while (Q--)
    {
        int t = inf.readInt(1, 3, "t");
        inf.readSpace();
        if (t == 1)
        {
            int x = inf.readInt(1, N - 1, "x");
            inf.readSpace();
            int y = inf.readInt(1, M, "y");
            --x, --y;
            ensuref(not lines.contains({y, x}), "line already exists");
            if (x > 0)
                ensuref(not lines.contains({y, x - 1}), "line already exists"); 
            if (x < N - 2)
                ensuref(not lines.contains({y, x + 1}), "line already exists");
            lines.insert({y, x});
        }
        else if (t == 2)
        {
            int x = inf.readInt(1, N - 1, "x");
            inf.readSpace();
            int y = inf.readInt(1, M, "y");
            x--, y--;
            ensuref(lines.contains({y, x}), "line does not exist");
            lines.erase({y, x});
        }
        else
        {
            int s = inf.readInt(1, N, "s");
        }
        inf.readEoln();
    }
    inf.readEof();
}
