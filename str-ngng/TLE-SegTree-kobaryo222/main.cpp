#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <cassert>

#include <atcoder/segtree>

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

struct Monoid {
    mint a, b, ab, ba, aba, bab, abab;
    Monoid()
        : a(0)
        , b(0)
        , ab(0)
        , ba(0)
        , aba(0)
        , bab(0)
        , abab(0)
    {
    }
};

Monoid e()
{
    return Monoid();
}

Monoid op(Monoid a, Monoid b)
{
    Monoid res;
    res.a = a.a + b.a;
    res.b = a.b + b.b;
    res.ab = a.ab + a.a * b.b + b.ab;
    res.ba = a.ba + a.b * b.a + b.ba;
    res.aba = a.aba + a.ab * b.a + a.a * b.ba + b.aba;
    res.bab = a.bab + a.ba * b.b + a.b * b.ab + b.bab;
    res.abab = a.abab + a.a * b.bab + a.ab * b.ab + a.aba * b.b + b.abab;
    return res;
};

int main()
{
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    long long Nsigma2 = 26LL * 26 * N * N;
    if (Nsigma2 > 100000000) {
        assert(false);
    }

    const int M = 26;
    vector<vector<atcoder::segtree<Monoid, op, e>>> seg(M, vector<atcoder::segtree<Monoid, op, e>>(M));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i == j)
                continue;
            vector<Monoid> v(N);
            for (int k = 0; k < N; k++) {
                if (S[k] == 'a' + i)
                    v[k].a = mint(1);
                if (S[k] == 'a' + j)
                    v[k].b = mint(1);
            }
            seg[i][j] = atcoder::segtree<Monoid, op, e>(v);
        }
    }

    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        mint ans = mint(0);
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                if (j == k)
                    continue;
                Monoid res = seg[j][k].prod(l, r);
                ans += res.abab;
            }
        }
        cout << ans.get() << endl;
    }
}