#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
template<typename T1,typename T2> bool chmin(T1 &a,T2 b){if(a<=b)return 0; a=b; return 1;}
template<typename T1,typename T2> bool chmax(T1 &a,T2 b){if(a>=b)return 0; a=b; return 1;}
int dx[4]={0,1,0,-1}, dy[4]={1,0,-1,0};
long double eps = 1e-9;
long double pi = acos(-1);

template< typename T, size_t N > istream &operator>>(istream &is, array< T, N > &a) {
    for(T &in : a) is >> in;
    return is;
}

template< typename T > istream &operator>>(istream &is, vector< T > &v) {
    for(T &in : v) is >> in;
    return is;
}

template< typename T > ostream &operator<<(ostream &os, const vector< T > &v) {
    for(int i = 0; i < (int) v.size(); i++) {
        os << v[i] << (i + 1 != (int) v.size() ? " " : "");
    }
    return os;
}

template< int mod = 1000000007 >
struct ModInt {
    int x;
    ModInt() : x(0) {}
    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    ModInt &operator+=(const ModInt &p) {
        if((x += p.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &p) {
        if((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &p) {
        x = (int) (1LL * x * p.x % mod);
        return *this;
    }
    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ModInt operator-() const { return ModInt(-x); }
    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    bool operator==(const ModInt &p) const { return x == p.x; }
    bool operator!=(const ModInt &p) const { return x != p.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while(b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt ret(1), mul(x);
        while(n > 0) {
            if(n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt< mod >(t);
        return (is);
    }

    static int get_mod() { return mod; }
};

// const int mod = 1000000007;
const int mod = 998244353;
using mint = ModInt< mod >;
const int MAX = 5100005;

mint fac[MAX], finv[MAX], inv[MAX], beki[MAX];

// テーブルを作る前処理
void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    beki[0] = 1;
    for (int i = 1; i < MAX; i++){
        fac[i] = fac[i - 1] * i;
        beki[i] = beki[i - 1] * 2;
    }
    finv[MAX-1] = fac[MAX-1].inverse();
    for(int i=MAX-2;i>=1;i--){
        finv[i] = finv[i+1]*(i+1);
        inv[i+1] = fac[i]*finv[i+1];
    }
}

// 二項係数計算
mint COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k]);
}

vector<int> a,b;
mint f(vector<int> v) {
    if(v.size() < 3) return 0;
    int n = v.size();
    int ma = 4200;
    int cnt[ma + 1] = {};
    for(int i=0;i<n;i++) {
        cnt[v[i]]++;
    }
    static mint dp[4444][4][4444];
    for(int i=0;i<4444;i++) {
        for(int j=0;j<4;j++) {
            for(int k=0;k<4444;k++) {
                dp[i][j][k] = 0;
            }
        }
    }
    dp[0][0][0] = 1;
    for(int i=0;i<ma;i++) {
        for(int j=0;j<=3;j++) {
            for(int k=0;k<ma;k++) {
                if(dp[i][j][k] == 0) continue;
                // not use
                dp[i+1][j][k] += dp[i][j][k];

                // use
                for(int c=1;c<=cnt[i];c++) {
                    if(k+c*i >= ma) break;
                    dp[i+1][min(j+c,3)][k+c*i] += dp[i][j][k] * COM(cnt[i],c);
                }
            }
        }
    }
    mint ret = 0;
    for(int i=0;i<ma;i++) {
        ret += dp[ma][3][i];
    }
    return ret;
}


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(20);

    int n;
    cin>>n;
    a.resize(n);
    b.resize(n);
    cin>>a>>b;

    mint ans = 0;
    COMinit();

    // cond 1
    ans += COM(n,2) + n;
    // cerr << ans << endl;

    // cond 2
    ll cnt = 0;
    vector<int> p,q;
    for(int i=0;i<n;i++) {
        if(max(a[i], b[i]) < 1600) {
            cnt++;
            p.push_back(max(a[i], b[i]));
        }
        if(max(a[i], b[i]) < 4200) {
            q.push_back(max(a[i], b[i]));
        }
    }
    for(int i=3;i<=cnt;i++) {
        ans += COM(cnt,i);
    }
    // cerr << "2 " << ans << endl;
    // cerr << "3 " << f(idx) << " " << f(idx2) << endl;

    ans -= f(p);
    ans += f(q);
    cout << ans << endl;

}
