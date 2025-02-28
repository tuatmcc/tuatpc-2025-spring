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
    vector<mint> inv(D);
    inv[1] = 1;
    for(int i = 2; i < D; ++i) inv[i] = -inv[MOD % i] * (MOD / i);

    auto exp = [&](vector<mint> &f) -> vector<mint> {
        vector<mint> F(D), Fd(D), fd(D);
        for(int i = 1; i < D; ++i) fd[i - 1] = Fd[i - 1] = f[i] * i;
        for(int i = 1; i < D; ++i){
            F[i] = Fd[i - 1] * inv[i];
            for(int j = 0; i + j < D; ++j){
                Fd[i + j] += F[i] * fd[j];
            }
        }
        return F;
    };

    auto subset_sum = [&](vector<mint> &cnt) -> mint {
        vector<mint> f(D);
        for(int i = 1; i < D; ++i){
            for(int j = 1; i * j < D; ++j){
                if(j & 1) f[i * j] += cnt[i] * inv[j];
                else f[i * j] -= cnt[i] * inv[j];
            }
        }
        auto F = exp(f);
        mint ret = 0;
        for(int i = 1; i < D; ++i) ret += F[i];
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
        vector<mint> cnt(D);
        for(int i = 0; i < N; ++i) if(M[i] < D) cnt[M[i]] += 1;
        S2 = subset_sum(cnt);
    }

    // S12 ... 最大値が 1600 未満かつ総和が 4200 未満のチームの総数
    mint S12;
    {
        vector<mint> cnt(D);
        for(int i = 0; i < N; ++i) if(M[i] < R) cnt[M[i]] += 1;
        S12 = subset_sum(cnt);
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
            if(M[i] < R) continue;
            T += distance(lower_bound(M.begin(), M.begin() + i, D - M[i]), M.begin() + i);
        }
    }

    cout << S + T << endl;
}