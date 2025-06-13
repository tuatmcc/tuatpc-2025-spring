#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 60);

void solve(){
    int X, Y, R; cin >> X >> Y >> R, --X, --Y, --R;
    vector<ll> A(4); for(auto &a : A) cin >> a;
    ll x = A[X], y = A[Y], a = INF, b = INF, ai, bi;
    for(int i = 0; i < 4; ++i){
        if(i == X or i == Y) continue;
        if(a == INF) a = A[i], ai = i;
        else b = A[i], bi = i;
    }

    ll ok = INF, ng = -1;
    array<tuple<ll, int, bool>, 4> B;
    while(abs(ok - ng) > 1){
        ll md = (ok + ng) >> 1;
        B[0] = {x + md * 4, -X, true};
        B[1] = {y - md * 2, -Y, false};
        B[2] = {a - md * 1, -ai, false};
        B[3] = {b - md * 1, -bi, false};
        sort(B.rbegin(), B.rend());
        for(int i = 1; i < 4; ++i) get<2>(B[i]) |= get<2>(B[i - 1]);
        if(get<2>(B[R])) ok = md;
        else ng = md;
    }

    auto check = [&](){
        B[0] = {x + ok * 4, -X, true};
        B[1] = {y - ok * 2, -Y, false};
        B[2] = {a - ok * 1, -ai, false};
        B[3] = {b - ok * 1, -bi, false};
        sort(B.rbegin(), B.rend());
        return get<2>(B[R]);
    };

    if(check()) cout << ok << endl;
    else cout << -1 << endl;
}

int main(){
    cin.tie(0)->sync_with_stdio(false);
    int T; cin >> T;
    while(T--) solve();
}