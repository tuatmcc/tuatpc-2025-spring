#include "testlib.h"
#include "constrains.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int W = inf.readInt(MIN_W, MAX_W, "W");
    inf.readSpace();
    int H = inf.readInt(MIN_H, MAX_H, "H");
    inf.readEoln();
    int Q = inf.readInt(MIN_Q, MAX_Q, "Q");
    inf.readEoln();

    vector<vector<bool>> lines(H, vector<bool>(W - 1, false));
    while (Q--) {
        int t = inf.readInt(1, 3, "t");
        inf.readSpace();
        if (t == 1) {
            int x = inf.readInt(1, W - 1, "x");
            inf.readSpace();
            int y = inf.readInt(1, H, "y");
            inf.readEoln();
            x--, y--;
            ensuref(!lines[y][x], "line already exists");
            if (x > 0)
                ensuref(!lines[y][x - 1], "line already exists left");
            if (x < W - 2)
                ensuref(!lines[y][x + 1], "line already exists right");
            lines[y][x] = true;
        } else if (t == 2) {
            int x = inf.readInt(1, W - 1, "x");
            inf.readSpace();
            int y = inf.readInt(1, H, "y");
            inf.readEoln();
            x--, y--;
            assert(lines[y][x]);
            lines[y][x] = false;
        } else {
            int s = inf.readInt(1, W, "s");
            inf.readEoln();
        }
    }
    inf.readEof();
}
