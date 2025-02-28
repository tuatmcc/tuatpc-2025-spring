#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

template< int mod >
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
        if(n == 0) return ModInt(1);
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

const int MOD = 998244353;
using mint = ModInt<MOD>;

int main(){
    int N; cin >> N;
    vector<int> A(N), B(N);
    for(int i = 0; i < N; ++i) cin >> A[i];
    for(int i = 0; i < N; ++i) cin >> B[i];

    const int R = 1600;
    const int D = 4200;

    auto subset_sum = [](vector<int> &rate) -> mint {
        int n = rate.size();
        vector dp(n + 1, vector(D, mint(0)));
        dp[0][0] = 1;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < D; ++j){
                dp[i + 1][j] += dp[i][j];
                if(j + rate[i] < D) dp[i + 1][j + rate[i]] += dp[i][j];
            }
        }
        mint ret;
        for(int i = 1; i < D; ++i) ret += dp.back()[i];
        return ret;
    };

    vector<int> M(N);
    for(int i = 0; i < N; ++i) M[i] = max(A[i], B[i]);
    sort(M.begin(), M.end());

    // S1 ... 最大値が 1600 未満のチームの総数
    mint S1 = 1;
    for(int i = 0; i < N; ++i) if(M[i] < R) S1 *= 2;
    S1 -= 1;

    // S2 ... 総和が 4200 未満のチームの総数
    mint S2;
    {
        vector<int> rate;
        for(int i = 0; i < N; ++i) if(M[i] < D) rate.push_back(M[i]);
        S2 = subset_sum(rate);
    }

    // S12 ... 最大値が 1600 未満かつ総和が 4200 未満のチームの総数
    mint S12;
    {
        vector<int> rate;
        for(int i = 0; i < N; ++i) if(M[i] < R) rate.push_back(M[i]);
        S12 = subset_sum(rate);
    }

    
    mint S = S1 + S2 - S12;

    // T ... 1 or 2 人チームで、最大値が 1600 以上かつ総和が 4200 以上のチームの総数
    mint T;
    {
        // 1 人チーム
        for(int i = 0; i < N; ++i) if(M[i] >= D) T += 1;
    }
    {
        // 2 人チーム
        for(int i = 0; i < N; ++i){
            for(int j = i + 1; j < N; ++j){
                if(M[i] + M[j] >= D and max(M[i], M[j]) >= R) T += 1;
            }
        }
    }

    cout << S + T << endl;
}