#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>

using namespace std;

struct Query {
    int l, r, index;
    Query(int l, int r, int index) : l(l), r(r), index(index) {}
};

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

int main()
{
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    vector<Query> queries;
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        --l;
        queries.emplace_back(l, r, i);
    }

    // 要調整
    const int block_size = N / min<int>(N, sqrt(Q));
    auto comp = [block_size](const Query& a, const Query& b) {
        int block_a = a.l / block_size, block_b = b.l / block_size;
        if (block_a != block_b)
            return block_a < block_b;
        // ブロック番号の偶奇でソート順を変える
        if (block_a % 2 == 1)
            return a.r > b.r;
        else
            return a.r < b.r;
    };
    sort(queries.begin(), queries.end(), comp);

    // 文字種
    const int M = 26;
    // lsum[a][b] := 区間内に存在する各文字 a について、それより左にある b の数の総和
    // rsum[a][b] := 区間内に存在する各文字 a について、それより右にある b の数の総和
    vector<vector<mint>> lsum(M, vector<mint>(M)), rsum(M, vector<mint>(M));
    // mid[a] := 区間内に存在する各文字 a について、それらの左右にある同じ文字の組の総和
    // cnt[a] := 区間内に存在する文字 a の数
    vector<mint> mid(M);
    vector<int> cnt(M);
    int l = 0, r = 0;
    mint cans = 0;

    auto add_left = [&]() {
        int c = S[l - 1] - 'a'; // 新しく追加される文字
        cans += mid[c]; // c + (? + c + ?)
        for (int i = 0; i < M; i++) {
            if (i == c)
                continue;
            mid[i] += rsum[i][c];
            lsum[i][c] += cnt[i];
            rsum[c][i] += cnt[i];
        }
        cnt[c]++;
        l--;
    };
    auto add_right = [&]() {
        int c = S[r] - 'a'; // 新しく追加される文字
        cans += mid[c]; // (? + c + ?) + c
        for (int i = 0; i < M; i++) {
            if (i == c)
                continue;
            mid[i] += lsum[i][c];
            lsum[c][i] += cnt[i];
            rsum[i][c] += cnt[i];
        }
        cnt[c]++;
        r++;
    };
    auto erase_left = [&]() {
        int c = S[l] - 'a'; // 削除される文字
        cans -= mid[c]; // c + (? + c + ?)
        for (int i = 0; i < M; i++) {
            if (i == c)
                continue;
            mid[i] -= rsum[i][c];
            lsum[i][c] -= cnt[i];
            rsum[c][i] -= cnt[i];
        }
        cnt[c]--;
        l++;
    };
    auto erase_right = [&]() {
        int c = S[r - 1] - 'a'; //  削除される文字
        cans -= mid[c]; // (? + c + ?) + c
        for (int i = 0; i < M; i++) {
            if (i == c)
                continue;
            mid[i] -= lsum[i][c];
            lsum[c][i] -= cnt[i];
            rsum[i][c] -= cnt[i];
        }
        cnt[c]--;
        r--;
    };

    vector<mint> ans(Q);
    for (const auto& query : queries) {
        while (l > query.l)
            add_left();
        while (r < query.r)
            add_right();
        while (l < query.l)
            erase_left();
        while (r > query.r)
            erase_right();
        ans[query.index] = cans;
    }

    for (auto& x : ans)
        cout << x << '\n';
}