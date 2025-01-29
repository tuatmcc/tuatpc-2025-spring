#include "testlib.h"
#include "constraints.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    int M = inf.readInt(MIN_M, MAX_M, "M");
    inf.readEoln();
    int Q = inf.readInt(MIN_Q, MAX_Q, "Q");
    inf.readEoln();

    set<pair<int, int>> lines_lefts;
    // while (Q--) {
    for (int i = 0; i < Q; i++) {
        int t = inf.readInt(1, 3, "t");
        inf.readSpace();
        if (t == 1) {
            int x = inf.readInt(1, N - 1, "x");
            inf.readSpace();
            int y = inf.readInt(1, M, "y");
            inf.readEoln();
            ensuref(!lines_lefts.contains({x, y}), std::format("line does not exist at ({}, {}) when {}", x, y, i).c_str());
            ensuref(!lines_lefts.contains({x - 1, y}), std::format("line already exists left at ({}, {}) when {}", x - 1, y, i).c_str());
            ensuref(!lines_lefts.contains({x + 1, y}), std::format("line already exists right at ({}, {}) when {}", x + 1, y, i).c_str());
            lines_lefts.insert({x, y});
        } else if (t == 2) {
            int x = inf.readInt(1, N - 1, "x");
            inf.readSpace();
            int y = inf.readInt(1, M, "y");
            inf.readEoln();
            ensuref(lines_lefts.contains({x, y}), "line does not exist");
            lines_lefts.erase({x, y});
        } else {
            int s = inf.readInt(1, N, "s");
            inf.readEoln();
        }
    }
    inf.readEof();
}
