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
    cin.tie(0)->sync_with_stdio(false);
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

    vector<int> C(N);
    for(int i = 0; i < N; ++i) C[i] = max(A[i], B[i]);
    sort(C.begin(), C.end());

    mint X1 = [&]{
        mint ret = 1;
        for(auto c : C) if(c < R) ret *= 2;
        return ret - 1;
    }();

    mint X2 = [&]{
        vector<mint> cnt(D);
        for(int i = 0; i < N; ++i) if(C[i] < D) cnt[C[i]] += 1;
        return subset_sum(cnt);
    }();

    mint X12 = [&]{
        vector<mint> cnt(D);
        for(int i = 0; i < N; ++i) if(C[i] < R) cnt[C[i]] += 1;
        return subset_sum(cnt);
    }();
   
    mint Y = [&]{
        mint ret = 0;
        for(const int &c : C) if(c >= D) ret += 1;
        for(int i = 0; i < N; ++i){
            if(C[i] < R) continue;
            ret += distance(lower_bound(C.begin(), C.begin() + i, D - C[i]), C.begin() + i);
        }
        return ret;
    }();

    cout << X1 + X2 - X12 + Y << endl;
}