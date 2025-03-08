#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using ld = long double;
using vd = vector<ld>;
using vvd = vector<vd>;

struct Edge {
    ll from, to;
    ld prob;
    Edge(ll from, ll to, ld prob) : from(from), to(to), prob(prob) {}
};

using Graph = vector<vector<Edge>>;

int main() {
    int n, l;
    cin >> n >> l;
    vl s(l);
    for (int i = 0; i < l; i++) cin >> s[i];
    Graph G(n);
    vl x(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m >> x[i];
        vector<ll> v(m);
        vector<ll> w(m);
        for (int j = 0; j < m; j++) {
            cin >> v[j];
            v[j]--; 
        }
        for (int j = 0; j < m; j++) cin >> w[j];
        for (int j = 0; j < m; j++) G[i].emplace_back(i, v[j], w[j] / 100.0); 
    }

    if (l == 1) {
        for (int i = 0; i < n; i++) {
            if (x[i] == s[0]) cout << "1 1\n";
            else cout << "0 1\n";
        }
        return 0;
    }

    // dp[i][j]: S_i からスタートし、j にいるときの確率
    vvd dp(l, vd(n, 0));
    for (int i = 0; i < n; i++){
        dp[l - 1][i] = (x[i] == s[l - 1] ? 1.0 : 0.0);
    }

    for (int i=l-2; i>=0; i--) {
        for (int j = 0; j < n; j++) {
            if (x[j] != s[i]) continue;
            for (auto &[u, v, prob] : G[j]) {
                dp[i][j] += dp[i + 1][v] * prob;
            }
        }
    }

    auto gcd = [&](ll a, ll b) -> ll {
        while (b != 0) {
            ll r = a % b;
            a = b;
            b = r;
        }
        return a;
    };

    ll d = 1;
    for (int i = 1; i < l; i++) d *= 100;
    for (int k = 0; k < n; k++) {
        ll num = round(dp[0][k] * d);
        ll g = gcd(num, d);
        ll a = num / g;
        ll b = d / g;
        cout << a << " " << b << "\n";
    }
}