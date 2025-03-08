#include <bits/stdc++.h>

#include "constraints.h"
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    int M, N, Q;

    // Validationの開始
    registerValidation(argc, argv);

    /**
     * 入力
     * N M
     * Q
     */
    N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    M = inf.readInt(MIN_M, MAX_M, "M");
    inf.readEoln();
    Q = inf.readInt(MIN_Q, MAX_Q, "Q");
    inf.readEoln();

    /**
     * query =>
     * 1 x y
     * 2 x y
     * 3 s
     *
     * query1
     * query2
     * ...
     * queryQ
     */
    set<pair<int, int>> lines;
    for (int i = 0; i < Q; i++) {
        int t = inf.readInt(1, 3, "t"), a, b;
        inf.readSpace();
        switch (t) {
            case 1:
                a = inf.readInt(1, N - 1, "x");
                inf.readSpace();
                b = inf.readInt(1, M, "y");
                ensuref(!lines.count({a, b}),
                        "query %d -> 1 %d %d: line is already exist", i + 1, a,
                        b);
                ensuref(!lines.count({a - 1, b}) || !lines.count({a + 1, b}),
                        "query %d -> 1 %d %d: line is exist left or right",
                        i + 1, a, b);
                lines.insert({a, b});
                break;
            case 2:
                a = inf.readInt(1, N - 1, "x");
                inf.readSpace();
                b = inf.readInt(1, M, "y");
                ensuref(lines.count({a, b}),
                        "query %d -> 2 %d %d: line is not exist", i + 1, a, b);
                lines.erase({a, b});
                break;
            case 3:
                a = inf.readInt(1, N, "s");
                break;
        }
        inf.readEoln();
    }
    inf.readEof();

    return 0;
}