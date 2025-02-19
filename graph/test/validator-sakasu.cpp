#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vl = vector<ll>;
// constraints
struct Parameter {
    ll MIN_N, MAX_N;
    ll MIN_V; 
    ll MIN_M, MAX_M, MAX_SUM_M;
    ll MIN_W, MAX_W;
    ll SUM_W;
    ll MIN_L, MAX_L;
};
constexpr Parameter param = {
    .MIN_N = 1,
    .MAX_N = 100'000,
    .MIN_V = 1,
    .MIN_M = 1,
    .MAX_M = 100,
    .MAX_SUM_M = 100'000,
    .MIN_W = 1,
    .MAX_W = 100,
    .SUM_W = 100,
    .MIN_L = 1,
    .MAX_L = 8
};

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    // (1)
    ll N = inf.readInt(param.MIN_N, param.MAX_N, "N");
    inf.readEoln();
    // (2)
    auto Xs = inf.readTokens(N, "[A-G]", "X");
    inf.readEoln();
    ll sum_M = 0;
    for (int i = 0; i < N; ++i){
        //(3)
        ll M = inf.readInt(param.MIN_M, min(N, param.MAX_M), "M");
        sum_M += M;
        inf.readEoln();
        //(5)
        auto V = inf.readInts(M, param.MIN_V, N, "V");
        assert(std::is_sorted_until(V.begin(), V.end()) == V.end());
        inf.readEoln();
        //(6)
        auto W = inf.readInts(M, param.MIN_W, param.MAX_W, "W");
        //(7)
        assert(reduce(W.begin(), W.end()) == param.SUM_W);
        inf.readEoln();
    }
    // (4)
    assert(sum_M <= min(N * N, param.MAX_SUM_M));
    // (8)
    ll L = inf.readInt(param.MIN_L, param.MAX_L, "L");
    inf.readEoln();
    // (9)
    string S = inf.readToken(format("[A-G]{%lld}", L), "S");
    inf.readEoln();
    inf.readEof();
    return 0;
}

#ifdef input_style
N S
#endif