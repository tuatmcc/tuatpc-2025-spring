#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
// #include <atcoder/modint>
// #include <atcoder/segtree>
// #include <atcoder/lazysegtree>
// #include <atcoder/dsu>
using namespace atcoder;

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

typedef long long int ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef priority_queue<pll, vpll, function<bool(pll,pll)> > pqpll; 
typedef priority_queue<ll, vll, function<bool(pll,pll)> > pqll;
 
struct edge{ ll to, cost; edge(ll e_to,ll e_cost): to(e_to), cost(e_cost){} };
typedef vector<vector<edge>> Graph;
 
#define rep(i,a,n) for(ll i = a;i < n;i++)
#define rrep(i,a,n) for(ll i = n-1; i >= a;i--)
#define LINF (1LL << 60)
#define INF (1 << 30)
#define fs first
#define sc second
#define EPS (ld)1e-10
#define ALL(a) a.begin(), a.end()
#define tcheck(a) if((clock() - start)/(ld)CLOCKS_PER_SEC >= a) break
#define debug(s) cout << #s << endl
#define debugval(x) cout << #x" = " << x << endl
 
template<typename T> ll sz(vector<T> &pos){ return (ll)pos.size(); }
template<typename T> ll sz(priority_queue<T, vector<T> > &que) {return (ll)que.size(); }
template<typename T> ll sz(priority_queue<T, vector<T>, greater<T> > &que) {return (ll)que.size(); }
ll sz(string &s) {return (ll)s.size(); } 
 
template<typename T> void chmin(T &a, T b) { if(a > b) a = b; }
template<typename T> void chmax(T &a, T b) { if(a < b) a = b; }
 
ll gcd(ll a,ll b){ return ((!b) ?a :gcd(b, a%b)); }
ll lcm(ll a,ll b){ return a / gcd(a,b) * b; }
ll dx[4] = {0,-1,0,1},dy[4] = {-1,0,1,0};
// ll dx[8] = {0,-1,-1,-1,0,1,1,1},dy[8] = {-1,-1,0,1,1,1,0,-1};
inline bool isinside(ll i,ll n){ return (i < n && i >= 0); }

using mint = modint998244353;
mint series(ll &r, ll &c, ll maxc, vector<string> &s);
mint parallel(ll &r, ll &c, vector<string> &s);

mint curcuit(ll r, ll c, ll maxc, vector<string> &s){
    mint res = 0;

    assert(s[r][c] == 'o'); c++;
    res = series(r,c,maxc-1,s);
    assert(s[r][c] == 'o'); c++;    
    
    return res;
}

mint series(ll &r, ll &c, ll maxc, vector<string> &s){
    mint res = 0;

    while(c <= maxc && s[r][c] == '-') c++;
    while(c <= maxc){
        res += parallel(r, c, s);
        while(c <= maxc && s[r][c] == '-') c++;
    }

    return res;
}

mint parallel(ll &r, ll &c, vector<string> &s){
    if(s[r][c] == '^'){
        assert(s[r].substr(c,6) == "^v^v^v"); c += 6;
        return mint(1);
    }

    std::cerr << "r, c # => " << r << ", " << c << std::endl;
    
    // maxc の計算
    ll tempr = r+1;
    while(tempr+1 < sz(s) && s[tempr+1][c] == '|') tempr++;
    ll tempc = c+1;
    while(tempc+1 < sz(s[tempr]) && s[tempr][tempc] == ' ') tempc++;
    assert(s[tempr][tempc] == '|'); 
    ll maxc = tempc;


    vector<mint> results;
    ll initial_r = r, initial_c = c;
    while(r < sz(s) && s[r][c] == '+'){
        assert(s[r][c] == '+'); c++;
        results.emplace_back(series(r,c,maxc-1,s));
        assert(s[r][c] == '+' && c == maxc); c++;

        if(r+1 >= sz(s) || s[r+1][initial_c] == ' '){
            r = initial_r;
            c = maxc + 1;
            break;
        }

        r++; c = initial_c;
        while(r < sz(s) && s[r][c] == '|') r++;
    }


    mint res = 0;
    for(auto result : results) res += result.inv();
    return res.inv();
}

void solve(){
    ll n; cin >> n;
    cin.ignore();

    vector<string> s(n);
    ll maxlen = 0;
    rep(i,0,n) getline(cin, s[i]), chmax(maxlen, sz(s[i]));
    std::cerr << "n # => " << n << std::endl;
    for (auto line : s) std::cerr << line << std::endl;
    rep(i,0,n) s[i].resize(maxlen);

    cout << curcuit(0,0,maxlen-1,s).val() << endl;
}

int main(){
    ll t; cin >> t;
    rep(testcase,0,t){
        std::cerr << "#### case " << t << std::endl;
        solve();
    }
}