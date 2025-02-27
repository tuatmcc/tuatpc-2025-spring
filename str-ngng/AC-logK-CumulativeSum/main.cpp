#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

/**
 * @brief Modint
 * @cite https://nyaannyaan.github.io/library/modint/modint.hpp
 */

 template <uint32_t mod>
 struct LazyMontgomeryModInt {
     using mint = LazyMontgomeryModInt;
     using i32 = int32_t;
     using u32 = uint32_t;
     using u64 = uint64_t;
 
     static constexpr u32 get_r() {
         u32 ret = mod;
         for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
         return ret;
     }
 
     static constexpr u32 r = get_r();
     static constexpr u32 n2 = -u64(mod) % mod;
     static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
     static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");
     static_assert(r * mod == 1, "this code has bugs.");
 
     u32 a;
 
     constexpr LazyMontgomeryModInt() : a(0) {}
     constexpr LazyMontgomeryModInt(const int64_t &b)
             : a(reduce(u64(b % mod + mod) * n2)){};
 
     static constexpr u32 reduce(const u64 &b) {
         return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
     }
 
     constexpr mint &operator+=(const mint &b) {
         if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
         return *this;
     }
 
     constexpr mint &operator-=(const mint &b) {
         if (i32(a -= b.a) < 0) a += 2 * mod;
         return *this;
     }
 
     constexpr mint &operator*=(const mint &b) {
         a = reduce(u64(a) * b.a);
         return *this;
     }
 
     constexpr mint &operator/=(const mint &b) {
         *this *= b.inverse();
         return *this;
     }
 
     constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
     constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
     constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
     constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
     constexpr bool operator==(const mint &b) const {
         return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
     }
     constexpr bool operator!=(const mint &b) const {
         return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
     }
     constexpr mint operator-() const { return mint() - mint(*this); }
     constexpr mint operator+() const { return mint(*this); }
 
     constexpr mint pow(u64 n) const {
         mint ret(1), mul(*this);
         while (n > 0) {
             if (n & 1) ret *= mul;
             mul *= mul;
             n >>= 1;
         }
         return ret;
     }
 
     constexpr mint inverse() const {
         int x = get(), y = mod, u = 1, v = 0, t = 0, tmp = 0;
         while (y > 0) {
             t = x / y;
             x -= t * y, u -= t * v;
             tmp = x, x = y, y = tmp;
             tmp = u, u = v, v = tmp;
         }
         return mint{u};
     }
 
     friend ostream &operator<<(ostream &os, const mint &b) {
         return os << b.get();
     }
 
     friend istream &operator>>(istream &is, mint &b) {
         int64_t t;
         is >> t;
         b = LazyMontgomeryModInt<mod>(t);
         return (is);
     }
 
     constexpr u32 get() const {
         u32 ret = reduce(a);
         return ret >= mod ? ret - mod : ret;
     }
 
     static constexpr u32 get_mod() { return mod; }
 };
 
 constexpr long long mod = 998244353;
 using mint = LazyMontgomeryModInt<mod>;

using ll = long long;
using T = mint;
using P = pair<T, T>;
const int C = 26;

int main(){
    int N, Q; cin >> N >> Q;
    string S; cin >> S;

    // `c1[i][c]` := S の 0 文字目から i 文字目までに含まれる文字 c の個数
    vector c1(N + 1, vector(C, T{}));
    // `c2[i][c][d]` := S の 0 文字目から i 文字目までに含まれる (c < d)
    //                  部分文字列 cd の個数 (first)
    //                  部分文字列 dc の個数 (second)
    vector c2(N + 1, vector(C, vector(C, P{})));
    // `c3[i][c][d]` := S の 0 文字目から i 文字目までに含まれる (c < d)
    //                  部分文字列 cdc の個数 (first)
    //                  部分文字列 dcd の個数 (second)
    vector c3(N + 1, vector(C, vector(C, P{})));
    // `c4[i][c][d]` := S の 0 文字目から i 文字目までに含まれる (c < d)
    //                  部分文字列 cdcd の個数 (first)
    //                  部分文字列 dcdc の個数 (second)
    vector c4(N + 1, vector(C, vector(C, P{})));

    // c1 の前計算
    for(int i = 1; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j) c1[i][j] += c1[i - 1][j];
        c1[i][c] += 1;
    }
    // c2 の前計算
    for(int i = 2; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = j + 1; k < C; ++k){
                c2[i][j][k] = c2[i - 1][j][k];
            }
        }
        for(int d = 0; d < C; ++d){
            if(d == c) continue;
            if(c < d) c2[i][c][d].second += c1[i - 1][d];
            else c2[i][d][c].first += c1[i - 1][d];
        }
    }
    // c3 の前計算
    for(int i = 3; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = j + 1; k < C; ++k){
                c3[i][j][k] = c3[i - 1][j][k];
            }
        }
        for(int d = 0; d < C; ++d){
            if(d == c) continue;
            if(c < d) c3[i][c][d].first += c2[i - 1][c][d].first;
            else c3[i][d][c].second += c2[i - 1][d][c].second;
        }
    }
    // c4 の前計算
    for(int i = 4; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = j + 1; k < C; ++k){
                c4[i][j][k] = c4[i - 1][j][k];
            }
        }
        for(int d = 0; d < C; ++d){
            if(d == c) continue;
            if(c < d) c4[i][c][d].second += c3[i - 1][c][d].second;
            else c4[i][d][c].first += c3[i - 1][d][c].first;
        }
    }

    vector f1(C, T{});
    vector f2(C, vector(C, P{}));
    vector f3(C, vector(C, P{}));
    vector f4(C, vector(C, P{}));
    while(Q--){
        int l, r; cin >> l >> r, --l;
        T ans = 0;
        for(int i = 0; i < C; ++i) f1[i] = c1[r][i] - c1[l][i];
        for(int i = 0; i < C; ++i){
            for(int j = i + 1; j < C; ++j){
                f2[i][j].first = c2[r][i][j].first - c2[l][i][j].first;
                f2[i][j].first -= c1[l][i] * f1[j];
                f2[i][j].second = c2[r][i][j].second - c2[l][i][j].second;
                f2[i][j].second -= c1[l][j] * f1[i];
                f3[i][j].first = c3[r][i][j].first - c3[l][i][j].first;
                f3[i][j].first -= c1[l][i] * f2[i][j].second;
                f3[i][j].first -= c2[l][i][j].first * f1[i];
                f3[i][j].second = c3[r][i][j].second - c3[l][i][j].second;
                f3[i][j].second -= c1[l][j] * f2[i][j].first;
                f3[i][j].second -= c2[l][i][j].second * f1[j];
                f4[i][j].first = c4[r][i][j].first - c4[l][i][j].first;
                f4[i][j].first -= c1[l][i] * f3[i][j].second;
                f4[i][j].first -= c2[l][i][j].first * f2[i][j].first;
                f4[i][j].first -= c3[l][i][j].first * f1[j];
                ans += f4[i][j].first;
                f4[i][j].second = c4[r][i][j].second - c4[l][i][j].second;
                f4[i][j].second -= c1[l][j] * f3[i][j].first;
                f4[i][j].second -= c2[l][i][j].second * f2[i][j].second;
                f4[i][j].second -= c3[l][i][j].second * f1[i];
                ans += f4[i][j].second;
            }
        }
        cout << ans << endl;
    }
}