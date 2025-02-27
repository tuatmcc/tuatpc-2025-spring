#include "testlib.h"
#include <cassert>
#include <numeric>
using namespace std;

using ll = long long;
constexpr ll MIN_N = 1, MAX_N = 100000;
constexpr ll MIN_M = 1, MAX_M = 100;
constexpr ll MAX_SUM_M = 100000;
constexpr ll MIN_W = 1, MAX_W = 100;
constexpr ll MIN_L = 1, MAX_L = 8;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    ll N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readEoln();
    auto Xs = inf.readTokens(N, "[A-G]", "X");
    inf.readEoln();
    ll sum_M = 0;
    for(int i = 0; i < N; ++i){
        ll M = inf.readInt(MIN_M, min(N, MAX_M), "M");
        sum_M += M;
        inf.readEoln();
        auto Vs = inf.readInts(M, MIN_N, N, "V");
        for(int j = 1; j < M; ++j) assert(Vs[j] > Vs[j - 1]);
        inf.readEoln();
        auto Ws = inf.readInts(M, MIN_W, MAX_W, "W");
        assert(reduce(Ws.begin(), Ws.end()) == 100);
        inf.readEoln();
    }
    assert(sum_M <= min(N * N, MAX_SUM_M));
    ll L = inf.readInt(MIN_L, MAX_L, "L");
    inf.readEoln();
    string S = inf.readString(format("[A-G]{%lld}", L), "S");
    inf.readEof();
}