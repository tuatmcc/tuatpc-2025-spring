#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vl = vector<ll>;
using vvl = vector<vl>;

struct Edge{
    ll from, to; ld prob;
    Edge(ll from, ll to, ld prob): from(from), to(to), prob(prob) {}
    bool operator<(const Edge &e) const { return prob < e.prob; }
};

using Graph = vector<vector<Edge>>;
int main(){
    int n; cin >> n;
    Graph G(n);
    vector<char> x(n);
    for(int i=0; i<n; i++) cin >> x[i];
    for(int i=0; i<n; i++){
        int m; cin >> m;
        vector<ll> v(m);
        vector<ld> w(m);
        for(int j=0; j<m; j++) { cin >> v[j]; v[j]--; }
        for(int j=0; j<m; j++) cin >> w[j];
        for(int j=0; j<m; j++) G[i].emplace_back(Edge(i, v[j], w[j]));
    }    
    ll l; string s; cin >> l >> s;
    if (l == 1){
        for (int i = 0; i < n; i++){
            if (x[i] == s[0]) cout << "1 1\n";
            else cout << "0 1\n";
        }
        return 0;
    }
    vvl dp(l, vl(n));
    // dp[i][j] := S_iを頂点jで鳴らす場合の数の総和
    for (int i = 0; i < n; i++) dp[l-1][i] = (x[i] == s[l-1] ? 1 : 0);
    for (int i=l-2; i>= 0; i--){
        for (int j=0; j<n; j++){
            if (x[j] != s[i]) {
                dp[i][j] = 0;
                continue;
            }
            for (auto &[u, v, w] : G[j]) {
                dp[i][j] += dp[i+1][v] * w;
            }
        }
    }

    auto gcd = [&](ll a, ll b) -> ll {
        while(b != 0){
            ll r = a%b;
            a = b;
            b = r;
        }
        return a;
    };
    ll d = 1;
    for(int i=1; i<l; i++) d *= 100;
    for (int k = 0; k < n; k++) {
        ll num = dp[0][k];
        ll g = gcd(num, d);
        ll a = num / g;
        ll b = d / g;
        cout << a << " " << b << "\n";
    }
}